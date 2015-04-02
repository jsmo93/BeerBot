# BeerBot
Source code for Beer Retrieval Robot

### Introduction:
The Silva/Smolinski BeerBot is designed to provide beverage service to adults enjoying their favorite entertainment together. Televised sporting events, movies, and video games are constantly interrupted by the need to grab another brew from the fridge. BeerBot intends to solve this problem with an ordering system that will allow adults to select a bottled beverage from an available list and have it delivered straight to their feet.
	
### Proposed Approach:
BeerBot will rely on four states and various sensor inputs to accomplish its goals. The first state is the “Ordering” state, where it will rest on the home pad awaiting user input. Once the user selects a beverage, the state will be updated to “Retrieval”. In the “Retrieval” state BeerBot will use four infrared sensors to follow a black line to the fridge containing cold drinks. During this trip, a bumper sensor will be used to determine if there are any obstacles on the proposed path and will generate an error alerting the user to clear the path. Upon reaching a large black square (where all infrared sensors read black), BeerBot will stop and transition into the “Search and Load” state where it will use a robotic arm to open the refrigerator door. A USB camera and color tracking will identify the user selected beverage. The robotic arm will then grab said beverage, close the door, and then transition into the final state “Delivery.” The delivery state will use the same four infrared sensors and a new bumper sensor on the opposite side of the robot to return to the home pad (another large black square) without turning. When this square is reached, the user can take their beer from BeerBot and other users can place orders. Additional modifications to the world may be required, including modifications to the fridge to allow for easier opening and closing with the robotic arm.
	
### Proposed Schedule:
Sprint 1 – 3/21 to 3/26 – Finalize list of materials, order parts, create SW architecture diagrams
<br>Sprint 2 – 3/26 to 4/2 – Assemble robot base, create SW framework with state transitions
<br>Sprint 3 – 4/2 to 4/9 – Build and attach robotic arm, develop SW for states 1, 2, and 4
<br>Sprint 4 – 4/9 to 4/16 – Adjust robotic arm and develop SW for state 3
<br>Sprint 5 – 4/16 to 4/23 – Stress testing, edge cases, major bug fixes
<br>Sprint 6 – 4/23 to 4/30 – Testing and minor fixes
