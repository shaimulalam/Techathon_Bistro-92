Working Principle::
The system consists of an Arduino UNO connected to a 16x2 LCD display and four push buttons. Here's how it works:

Google Drive Video link:https://drive.google.com/file/d/14a3eWRBVgUlEqoX2-lSUQDHWrQhrZFRJ/view?usp=sharing

Menu Access and Navigation:

When the Menu button (Button 1) is pressed, the main menu is displayed on the LCD screen.

Up and Down buttons (Button 3 and 4) allow customers to scroll through menu items such as "Burger", "Pizza", "Pasta", and "Drinks".

Item Selection and Quantity Adjustment:

Pressing the Select button (Button 2) highlights a menu item and moves to the quantity selection phase.

Using the Up and Down buttons, the customer can increase or decrease the quantity.

Pressing Select again adds the selected item and quantity to the cart.

Order Finalization:

A long press (about 1.5 seconds) on the Select button submits the final order.

The system then displays "Placing Order..." and internally resets the cart after sending the order details (shown via Serial Monitor simulation).

Order Reset:

Pressing the Menu button at any time clears the current cart and restarts the order process.

This hardware-software integration mimics a real-world smart ordering device, making dining experiences smoother and more efficient.

Code Description
The Arduino code is structured as follows:

Library Initialization:
The LiquidCrystal library is used to control the LCD. The pins are defined for RS, Enable, and Data pins (D4–D7).

Button Setup:
Four buttons are connected to pins 6, 7, 8, and 9, with internal pull-up resistors enabled for reliable input handling.

Menu System:

An array menuItems[] holds the available menu items.

The customer navigates the menu using "Up" and "Down" buttons.

Pressing "Select" enters quantity selection mode.

Cart Management:

A structure CartItem stores selected items and their quantities.

Up to 5 items can be added to the cart before placing an order.

Order Placement:

A long press on the "Select" button triggers the placeOrder() function, displaying the order on the Serial Monitor.

Debounce and Long Press Handling:

Button presses are debounced using timing checks.

Long press duration is set at 1500 milliseconds to distinguish it from a normal press.

The code is efficient, modular, and easily extendable for adding more items or functionalities like cloud communication.

Connection
Here is how the components are connected based on the schematic diagram:

LCD Display (16x2) connections:

RS → Pin 12 (Arduino)

EN → Pin 11 (Arduino)

D4 → Pin 5 (Arduino)

D5 → Pin 4 (Arduino)

D6 → Pin 3 (Arduino)

D7 → Pin 2 (Arduino)

VSS, RW, LED- → GND (Arduino)

VDD, LED+ → 5V (Arduino)

VO (Contrast) → Middle terminal of a 250K potentiometer
(Other two terminals of the potentiometer connected to 5V and GND)

Push Buttons:

Menu Button (S1) → Pin 8

Select Button (S2) → Pin 9

Up Button (S3) → Pin 6

Down Button (S4) → Pin 7

Each button uses internal pull-up configuration.

Power Supply:

Arduino is powered through USB or 5V external supply.

Benefits of the Project
Reduces Customer Wait Time:
Customers can directly place orders from their tables without needing to wait for a server.

Minimizes Human Errors:
By automating order taking, mistakes caused by miscommunication are significantly reduced.

Enhances Customer Experience:
Smooth and fast ordering improves overall customer satisfaction.

Increases Restaurant Efficiency:
Staff can focus on food preparation and customer service rather than manually taking orders.

Scalable Solution:
The system is modular and can be upgraded easily to include wireless communication (e.g., Wi-Fi, cloud integration) for real-time kitchen updates.

Cost-Effective:
Built using simple and affordable hardware components like Arduino UNO, push buttons, and an LCD display.
