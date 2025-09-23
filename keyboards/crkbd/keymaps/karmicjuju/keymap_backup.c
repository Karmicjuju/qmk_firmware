// BACKUP OF ORIGINAL OLED FUNCTION
// You can restore this once OLED is confirmed working

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state)) {
            case L_BASE:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case L_SYM:
                oled_write_P(PSTR("Symbol\n"), false);
                break;
            case L_NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case L_APP:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undef\n"), false);
        }

        // Host Keyboard LED Status
        led_t led_state = host_keyboard_led_state();
        oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);

        // Mac/PC mode status
        oled_write_P(mac_mode ? PSTR("MAC") : PSTR("PC "), false);
    } else {
        // Corne logo or other graphic for secondary display
        static const char PROGMEM corne_logo[] = {
            // You can add a custom logo here
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
            0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
            0};
        oled_write_P(corne_logo, false);
    }
    return false;
}
#endif