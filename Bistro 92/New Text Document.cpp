#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// RS, E, D4, D5, D6, D7

// Button pins
const int buttonMenu = 8;
const int buttonSelect = 9;
const int buttonUp = 6;
const int buttonDown = 7;

// Long press detection
unsigned long buttonPressStart = 0;
bool isLongPressing = false;
const int longPressDuration = 1500; // ms

// Menu items
String menuItems[] = {"Burger", "Pizza", "Pasta", "Drinks"};
int menuSize = 4;
int menuIndex = 0;
int quantity = 1;
bool selectingQuantity = false;

// Cart system
struct CartItem {
  String item;
  int quantity;
};
CartItem cart[5];
int cartIndex = 0;

// Button debounce variables
unsigned long lastButtonPress = 0;
const int debounceDelay = 200;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(buttonMenu, INPUT_PULLUP);
  pinMode(buttonSelect, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);

  Serial.begin(9600);
  showMenu();
}

void loop() {
  // Handle button presses with debounce
  if (millis() - lastButtonPress > debounceDelay) {
    // Menu button press
    if (digitalRead(buttonMenu) == LOW) {
      resetCart();
      showMenu();
      lastButtonPress = millis();
    }

    // Long Press Handling for Select button
    if (digitalRead(buttonSelect) == LOW) {
      handleLongPress();
      lastButtonPress = millis();
    } else {
      isLongPressing = false;
    }

    // Handle Up and Down button presses for navigating menu and quantity
    if (!selectingQuantity) {
      handleMenuNavigation();
    } else {
      handleQuantityAdjustment();
    }
  }
}

// Handle long press on the select button
void handleLongPress() {
  if (!isLongPressing) {
    buttonPressStart = millis();
    isLongPressing = true;
  } else {
    if (millis() - buttonPressStart > longPressDuration) {
      placeOrder();
      delay(1500);
    }
  }
}

// Handle navigation through menu options
void handleMenuNavigation() {
  if (digitalRead(buttonUp) == LOW) {
    menuIndex = (menuIndex - 1 + menuSize) % menuSize;  // Wrap around menu
    showMenu();
    lastButtonPress = millis();
  }
  if (digitalRead(buttonDown) == LOW) {
    menuIndex = (menuIndex + 1) % menuSize;  // Wrap around menu
    showMenu();
    lastButtonPress = millis();
  }
  if (digitalRead(buttonSelect) == LOW) {
    selectingQuantity = true;
    quantity = 1;
    showQuantity();
    lastButtonPress = millis();
  }
}

// Handle quantity adjustments
void handleQuantityAdjustment() {
  if (digitalRead(buttonUp) == LOW) {
    quantity++;
    showQuantity();
    lastButtonPress = millis();
  }
  if (digitalRead(buttonDown) == LOW) {
    if (quantity > 1) quantity--;
    showQuantity();
    lastButtonPress = millis();
  }
  if (digitalRead(buttonSelect) == LOW) {
    if (cartIndex < 5) {
      cart[cartIndex].item = menuItems[menuIndex];
      cart[cartIndex].quantity = quantity;
      cartIndex++;
      Serial.print("Added to cart: ");
      Serial.print(menuItems[menuIndex]);
      Serial.print(" x ");
      Serial.println(quantity);
    } else {
      Serial.println("Cart is Full!");
    }
    selectingQuantity = false;
    showMenu();
    lastButtonPress = millis();
  }
}

// Show menu on LCD
void showMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select an Item:");
  lcd.setCursor(0, 1);
  lcd.print(menuItems[menuIndex]);
}

// Show quantity setting screen
void showQuantity() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Quantity:");
  lcd.setCursor(0, 1);
  lcd.print(menuItems[menuIndex]);
  lcd.print(" x");
  lcd.print(quantity);
}

// Function to place order
void placeOrder() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Placing Order...");
  Serial.println("Order Details:");
  for (int i = 0; i < cartIndex; i++) {
    Serial.print(cart[i].item);
    Serial.print(" x ");
    Serial.println(cart[i].quantity);
  }
  resetCart();
  delay(1000);
  showMenu();
}

// Reset cart
void resetCart() {
  cartIndex = 0;
  selectingQuantity = false;
  quantity = 1;
  menuIndex = 0;
  Serial.println("Cart Reset");
}
