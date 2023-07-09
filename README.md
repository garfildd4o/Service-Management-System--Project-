# Service Management System [Project]

This project aims to develop a computer program that implements an information system for a service management system. The program will store information about service orders, including order number, date, client name, device type (phone, tablet, laptop, monitor, TV, etc.), device serial number, client-reported problem (up to 50 characters), service technician name, repair details (up to 50 characters), price, duration of stay in the service center, and status (accepted order/rejected order/ reparation completed). The possible problems and repairs will be predefined in lists with a maximum of 20 entries each.

The program should include the following functionalities:

A. Menu with options to navigate through the program.
B. Addition of a new device for repair.
a. Add a single device.
b. Add a list of devices. Enter the number of devices followed by the respective device details.

Adding devices represents accepting a service order. Only partial information (order number, device type, serial number, etc.) is entered. The service technician's name, repair details, etc., are updated after the repair is performed.
C. Display all devices on the screen.
D. Data correction for a device.
a. Enter the order number and correct the data.
b. Rejection of a service order if it has not been repaired, with a penalty fee of 10 BGN.

E. Servicing of a device.
a. Enter the device's serial number and display its information.
b. Enter the name of the servicing technician, repair details, price, and status.

F. Audit of service orders in a submenu.
a. Display all service orders for a given month, sorted by serial number.
b. Display all repaired service orders for a specific device type, sorted by date in descending order.
c. Display all service orders for a specific client, sorted by device serial number.

G. The program's data should be able to be saved to a file and loaded between program executions.

Additional conditions:
a. When adding a service order, only the current date is allowed.
b. When displaying the client-reported problem or repair details, a submenu will show the predefined texts from the respective list, and the user can select the appropriate option without the need for manual input.
c. The training data stored in a binary file should be able to be saved to a text file and vice versa.
