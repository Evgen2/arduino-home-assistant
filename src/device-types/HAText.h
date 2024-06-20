#ifndef AHA_HAText_H
#define AHA_HAText_H

#include "HABaseDeviceType.h"

#ifndef EX_ARDUINOHA_TEXT

#define HAText_CALLBACK(name) void (*name)(HAText* sender)

/**
 * HAText represents a button that's displayed in the Home Assistant panel and
 * triggers some logic on your Arduino/ESP device once clicked.
 *
 * @note
 * You can find more information about this entity in the Home Assistant documentation:
 * https://www.home-assistant.io/integrations/text.mqtt/
 */
class HAText : public HABaseDeviceType
{
public:
    /**
     * @param uniqueId The unique ID. It needs to be unique in a scope of your device.
     */
    HAText(const char* uniqueId);


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

    /* Registers callback that will be called each time the number is changed in the HA panel.
     * Please note that it's not possible to register multiple callbacks for the same number.
     *
     * @param callback
     * @note In non-optimistic mode, the number must be reported back to HA using the HANumber::setState method.
     */
    inline void onCommand(HAText_CALLBACK(callback))
        { _commandCallback = callback; }



protected:
    virtual void buildSerializer() override;
    virtual void onMqttConnected() override;

private:

    void handleCommand(const uint8_t* cmd, const uint16_t length);

    HAText_CALLBACK(_commandCallback);

    /// The force update flag for the HA panel.
    bool _forceUpdate;

    /// The icon of the button. It can be nullptr.
    const char* _icon;


    /// The retain flag for the HA commands.
    bool _retain;

};

#endif
#endif
