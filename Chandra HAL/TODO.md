# Additions
1. Different blocking event methods: wait_until([low, high, rising, falling]), pulsein, etc.

2. Add the ability to set the frequency of a chandra::chrono::Timer as well as the duration. 

# Changes
1. Add init methods to all of the components that call enable by default.  This includes
  for components that do not strictly need an init method.  This should be the
  default method for getting a component in a usable condition.  Components that
  use other components (i.e. drivers that use a communication protocol), should
  call init on the components they use.

2. Add a clock template parameter to communication protocol drivers (USART, I2C,
  SPI, etc. ) so that timeout support is provided.  This might also suggest that
  a standard communication driver timeout interface should be provided.  For
  instance, read/write timeout; init timout; etc.

3. Make the default clock parameter a type alias that can be configured.  For
  instance, chandra::chrono::default_clock...
    using default_clock = chandra::chrono::timestamp_clock;
  This way, it is possible to change the default clock for all of the components
  in one go.

4. Integrate LPC_SYSCON->FCLKSEL[n] in I2C for base_clock select on LPC84x.
  I2C0->5, I2C1->6, I2C2->7, I2C3->8, n = 5 + x for I2Cx
