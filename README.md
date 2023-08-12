# RTOS_simple_project_atmega32_Binary_Semaphore

This project uses an ATmega32 microcontroller along with FreeRTOS and a binary semaphore to control an LED's blinking behavior in response to a button press. The binary semaphore serves as a signaling mechanism between two tasks: one task monitors the button state, and the other task controls the LED. When the button is pressed, the button task signals the LED task through the semaphore, causing the LED to blink. The LED blinks ever time the button is pressed again, repeating the cycle. This project showcases the integration of real-time multitasking and synchronization techniques to achieve a button-controlled LED blinking functionality.
 ![Uploading Binary Semaphore.png…]()
