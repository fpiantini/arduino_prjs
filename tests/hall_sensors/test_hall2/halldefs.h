#if !defined HALL_DEFS_INCLUDE
#define HALL_DEFS_INCLUDE

#define NUM_SENSORS_MAX 8

typedef struct {
  
  int led_pin;
  int num_sens;
  int hall_vcc_lines[NUM_SENSORS_MAX];

  // input used as hall sensor inputs
  int hall_pins_lines[NUM_SENSORS_MAX];

  // hall sensors state
  int hall_state[NUM_SENSORS_MAX];
  int one_active;

} HallArrayInfo_t;





#endif   // #if !defined HALL_DEFS_INCLUDE
