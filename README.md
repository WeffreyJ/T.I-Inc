# OLED Menu System with Rotary Encoder - Test and Demo

## **Overview**
This project is part of the TI Mentorship program supervised by **Prof. Albrecht**. It aims to integrate an OLED display and a rotary encoder to create a user-friendly interface system. The deliverables include various UI features such as splash screens, menu navigation, and a dynamic timer. The project's emphasis is on simplicity, functionality, and professional design, with future potential for integration into larger systems.

---

## **Project Details**

- **Project Name**: OLED Menu System with Rotary Encoder  
- **Start Date**: November 17, 2024  
- **Supervised By**: Prof. Albrecht  
- **Team Member**: Jeffrey Walker  
- **Goal**:  
  - Simulate, test, and demo display options with I2C OLED and a rotary encoder.  
  - Prioritize simplicity, functionality, and professional design.  
  - Build multiple demos, culminating in a final cohesive display system.  

---

## **Setup and Resources**

### **Hardware**
- **Parts**:  
  - Purchased as outlined in **"Notes from Prof. A"** (link provided in the repository).  
  - Includes an I2C OLED display and a rotary encoder module.  

### **Software**
- **Arduino IDE**: Used for coding and testing.  
- **Libraries**:  
  - `U8g2`: For OLED display control.  
  - Fonts:  
    - `u8g2_font_ncenB08_tr` (serif, for titles).  
    - `u8g2_font_helvB08_tr` (sans-serif, for menus and general text).  

---

## **Deliverables and Features**

### **Version 1.0: Loading Screen with Animation**
**Goal**:  
Demonstrate the integration of OLED display, rotary encoder, and UI design.

#### **Key Features**:
1. **Splash Screen**:
   - Displays `"Menu Demo"` and `"v1.0"` along with an optional bitmap logo.
   - Holds for 5 seconds on startup.

2. **Variable Display**:
   - Dynamically shows values of `Var 1` and `Var 2`.
   - Example:
     ```
     Var 1     Var 2
     1000      0.5
     ```
   - Optional battery indicator.

3. **Countdown Timer**:
   - Triggered by a rotary encoder button press.
   - Timer duration calculated as `(Var 1 * Var 2) / 100`.
   - Progress visually represented with a bar.

4. **Main Menu**:
   - Navigate using the rotary encoder.
   - Options include:
     - Adjust `Var 1`: Values: `100, 250, 500, 1000 (default), 2000`.
     - Adjust `Var 2`: Values: `0.5 (default), 1, 2, 4`.
     - **Calibrate**:
       - Modify a calibration factor (default = `0.0`).
       - Use rotary encoder to increment/decrement.
       - Save and exit on button press.

---

## **Activity Log**

| **Date**       | **Time**  | **Activity Description**                             | **Procedure/Details**                                                | **Outcome**                                           | **Next Steps**                                             |
|-----------------|-----------|-----------------------------------------------------|----------------------------------------------------------------------|-------------------------------------------------------|------------------------------------------------------------|
| **11/27/2024** | **3:44am**| Defined placeholders in Arduino IDE for deliverables.| Created calibration and animation functions, added splash screens.  | Halfway setup complete with rotary control and splash.| Refine encoder calibration, define variables, improve load animation. |

---

## **Notes from Prof. Albrecht**
- Focus on user interface simplicity and functionality.  
- Use placeholder fonts (`ncenB08_tr` and `helvB08_tr`) to test aesthetics.  
- Test each deliverable independently to ensure stability before integrating.  

---

## **Additional Information**
- **Repository**: All code and resources are available in the **TI Mentorship Repository** on GitHub.  
- **References**:
  - Arduino I2C tutorials.
  - U8g2 library documentation for fonts and OLED integration.  
- **Future Goals**:
  - Extend the project to include advanced animations and graphical interfaces.
  - Finalize a professional font selection after testing placeholders.  

---

This README provides an overview of the project and serves as a guide for understanding its objectives, setup, and progress. Feel free to contribute or reach out for clarification!
