// C:\workspace\Atmel Studio\6.1\FreeRTOSArduino-Test\HempsteadJoystick\src\joystick\TestHempJoy2.h


char ReportDescriptor[57] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x04,                    // USAGE (Joystick)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x09,                    //   USAGE_PAGE (Button)
    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
    0x29, 0x3f,                    //   USAGE_MAXIMUM (Button 63)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x35, 0x00,                    //   PHYSICAL_MINIMUM (0)
    0x45, 0x01,                    //   PHYSICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x3f,                    //   REPORT_COUNT (63)
    0x81, 0x22,                    //   INPUT (Data,Var,Abs,NPrf)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x81, 0x21,                    //   INPUT (Cnst,Ary,Abs,NPrf)
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    // USAGE (X)
    0x09, 0x31,                    // USAGE (Y)
    0x09, 0x32,                    // USAGE (Z)
    0x35, 0x00,                    // PHYSICAL_MINIMUM (0)
    0x46, 0xff, 0x0f,              // PHYSICAL_MAXIMUM (4095)
    0x15, 0x00,                    // LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x0f,              // LOGICAL_MAXIMUM (4095)
    0x75, 0x10,                    // REPORT_SIZE (16)
    0x95, 0x03,                    // REPORT_COUNT (3)
    0x81, 0x22,                    // INPUT (Data,Var,Abs,NPrf)
    0xc0                           // END_COLLECTION
};

