/** @file
 * @author Edouard DUPIN
 * @copyright 2010, Edouard DUPIN, all right reserved
 * @license BSD v3 (see license file)
 */


#include <appl/debug.hpp>
#include <appl/MainWindows.hpp>

#include <ewol/widget/Image.hpp>
#include <ewol/context/Context.hpp>
#include <eproperty/Value.hpp>

appl::MainWindows::MainWindows() :
  m_idDisplayed(-1) {
	APPL_DEBUG("CREATE WINDOWS ... ");
	addObjectType("appl::MainWindows");
}

void appl::MainWindows::init() {
	ewol::widget::Windows::init();
	m_image = ewol::widget::Image::create("src", etk::String("DATA:///icon.png"),
	                                      "expand", bvec2(true,true),
	                                      "fill", bvec2(true,true));
	propertyTitle.set("EVI");
	m_image->propertyExpand.set(bvec2(true,true));
	m_image->propertyFill.set(bvec2(true,true));
	setSubWidget(m_image);
	shortCutAdd("F12",          "menu:reloade-shader");
	signalShortcut.connect(sharedFromThis(), &appl::MainWindows::onCallbackShortCut);
}

void appl::MainWindows::onCallbackShortCut(const etk::String& _value) {
	APPL_WARNING("Event from ShortCut : " << _value);
	if (_value == "menu:reloade-shader") {
		ewol::getContext().getResourcesManager().reLoadResources();
		ewol::getContext().forceRedrawAll();
	} else {
		APPL_ERROR("Event from Menu UNKNOW : '" << _value << "'");
	}
}

void appl::MainWindows::setListOfFiles(etk::Vector<etk::Path> _listImages) {
	m_listImages = _listImages;
	if (m_listImages.size() == 0) {
		m_idDisplayed = -1;
		m_image->propertySource.set("DATA:///icon.png");
		propertyTitle.set("EVI");
	} else {
		m_idDisplayed = 0;
		m_image->propertySource.set(m_listImages[0]);
		propertyTitle.set("EVI:" + m_listImages[0].getString());
	}
}

bool appl::MainWindows::onEventInput(const ewol::event::Input& _event) {
	APPL_WARNING(" EVENT : " << _event);
	return true;
}

bool appl::MainWindows::onEventEntry(const ewol::event::Entry& _event) {
	if (m_idDisplayed == -1) {
		return false;
	}
	if (_event.getStatus() == gale::key::status::down) {
		if (    (    _event.getType() == gale::key::keyboard::character 
		          && _event.getChar() == ' ')
		     || _event.getType() == gale::key::keyboard::right) {
			m_idDisplayed++;
			if (m_idDisplayed >= m_listImages.size()) {
				m_idDisplayed--;
				return true;
			}
			m_image->propertySource.set(m_listImages[m_idDisplayed]);
			propertyTitle.set("EVI:" + m_listImages[m_idDisplayed].getString() + " " + etk::toString(m_idDisplayed+1) + "/" + etk::toString(m_listImages.size()));
			return true;
		}
		if (_event.getType() == gale::key::keyboard::left) {
			m_idDisplayed--;
			if (m_idDisplayed < 0) {
				m_idDisplayed++;
				return true;
			}
			m_image->propertySource.set(m_listImages[m_idDisplayed]);
			propertyTitle.set("EVI:" + m_listImages[m_idDisplayed].getString() + " " + etk::toString(m_idDisplayed+1) + "/" + etk::toString(m_listImages.size()));
			return true;
		}
		if (_event.getType() == gale::key::keyboard::down) {
			m_idDisplayed += 10;
			if (m_idDisplayed >= m_listImages.size()) {
				m_idDisplayed = m_listImages.size()-1;
			}
			m_image->propertySource.set(m_listImages[m_idDisplayed]);
			propertyTitle.set("EVI:" + m_listImages[m_idDisplayed].getString() + " " + etk::toString(m_idDisplayed+1) + "/" + etk::toString(m_listImages.size()));
			return true;
		}
		if (_event.getType() == gale::key::keyboard::up) {
			m_idDisplayed -= 10;
			if (m_idDisplayed < 0) {
				m_idDisplayed = 0;
			}
			m_image->propertySource.set(m_listImages[m_idDisplayed]);
			propertyTitle.set("EVI:" + m_listImages[m_idDisplayed].getString() + " " + etk::toString(m_idDisplayed+1) + "/" + etk::toString(m_listImages.size()));
			return true;
		}
		if (_event.getType() == gale::key::keyboard::pageDown) {
			m_idDisplayed = m_listImages.size()-1;
			m_image->propertySource.set(m_listImages[m_idDisplayed]);
			propertyTitle.set("EVI:" + m_listImages[m_idDisplayed].getString() + " " + etk::toString(m_idDisplayed+1) + "/" + etk::toString(m_listImages.size()));
			return true;
		}
		if (_event.getType() == gale::key::keyboard::pageUp) {
			m_idDisplayed = 0;
			m_image->propertySource.set(m_listImages[m_idDisplayed]);
			propertyTitle.set("EVI:" + m_listImages[m_idDisplayed].getString() + " " + etk::toString(m_idDisplayed+1) + "/" + etk::toString(m_listImages.size()));
			return true;
		}
	}
	
	return true;
}
