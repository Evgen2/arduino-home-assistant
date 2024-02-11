#ifndef AHA_HAText_H
#define AHA_HAText_H

#include "HABaseDeviceType.h"

#ifndef EX_ARDUINOHA_BUTTON

#define HAText_CALLBACK(name) void (*name)(HAText* sender)

/**
 * HAText represents a button that's displayed in the Home Assistant panel and
 * triggers some logic on your Arduino/ESP device once clicked.
 *
 * @note
 * You can find more information about this entity in the Home Assistant documentation:
 * https://www.home-assistant.io/integrations/button.mqtt/
 */
class HAText : public HABaseDeviceType
{
public:
    /**
     * @param uniqueId The unique ID of the button. It needs to be unique in a scope of your device.
     */
    HAText(const char* uniqueId);

    /**
     * Sets class of the device.
     * You can find list of available values here: https://www.home-assistant.io/integrations/button/#device-class
     *
     * @param deviceClass The class name.
     */
    inline void setDeviceClass(const char* deviceClass)
        { _class = deviceClass; }

    /**
     * Forces HA panel to process each incoming value (MQTT message).
     * It's useful if you want to have meaningful value graphs in history.
     *
     * @param forceUpdate
     */
    inline void setForceUpdate(bool forceUpdate)
        { _forceUpdate = forceUpdate; }

    /**
     * Sets icon of the button.
     * Any icon from MaterialDesignIcons.com (for example: `mdi:home`).
     *
     * @param icon The icon name.
     */
    inline void setIcon(const char* icon)
        { _icon = icon; }

    bool setValue(const char* value);

protected:
    virtual void buildSerializer() override;
    virtual void onMqttConnected() override;

private:
    /// The device class. It can be nullptr.
    const char* _class;

    /// The force update flag for the HA panel.
    bool _forceUpdate;

    /// The icon of the button. It can be nullptr.
    const char* _icon;


    /// The retain flag for the HA commands.
    bool _retain;

};

#endif
#endif
