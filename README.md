# Circle Collision Project

Hello! I am **AnimeManna**. It's nice to see you on my page!

This is a small C++ project that uses native C++ for calculate position and operations with vectors and using **Raylib** to render, handle click event and animate objects. It demonstrates how a ball moves toward a point clicked by the user.

---

## 🚀 How to Run the Project

### 1. **Clone the Repository**
```sh
git clone https://github.com/AnimeManna/vector-movement.git
cd vector-movement
```
2. Open the Project in Visual Studio
Launch Visual Studio.
Open the solution file (.sln) located in the root of the project.
3. Install Dependencies
This project uses the Raylib library installed via vcpkg.

If you don't have vcpkg, install it with the following commands:

```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat  # For Windows
./bootstrap-vcpkg.sh   # For Linux/Mac
```
Install Raylib using vcpkg:
```sh
vcpkg install raylib
```
Integrate vcpkg with Visual Studio:
```sh
vcpkg integrate install
```
4. Build the Project
In Visual Studio, press Ctrl + Shift + B to build the project.
Make sure the build configuration is set to Release or Debug.
5. Run the Project
After a successful build, press Ctrl + F5 or click "Start Without Debugging".
A window will open showing two circles. The green circle moves toward the red one, which you can reposition by clicking anywhere in the window.
## 🛠 Project Features

- **Dynamic movement of objects.**
- **Calculate collision**
- **Change character direction if object has collision
- **Rendering of primitives using Raylib.**


## 💡 Code Example
Here is the main function that calculates direction vector for cirlce that hsa collision:
```cpp
    if (character.collisions.size() > 0) {
        for (int i = 0; i < character.collisions.size(); i++) {
            GameObject curretCollisionItem = *character.collisions[i];
            Vector2 vectorBetweenObjects = Vector2({ curretCollisionItem.position.x - character.position.x, curretCollisionItem.position.y - character.position.y });
            float distanceBetweenObjects = getModuleOfVector(vectorBetweenObjects);
            float sumOfSize = character.size + curretCollisionItem.size;

            Vector2 collisionNormalizedVector = getNormalizedVector(character.position, curretCollisionItem.position);
            float dotByCords = directionVector.x * collisionNormalizedVector.x + directionVector.y * collisionNormalizedVector.y;


            float moduleOfVectors = getModuleOfVector(directionVector) * getModuleOfVector(collisionNormalizedVector);
            float cosOfVectors = dotByCords / moduleOfVectors;

            float tanOfTeta = sumOfSize / distanceBetweenObjects;
            float angleInRadians = atan(tanOfTeta);

            float angleTolerance = 0.5f;

            bool isRightDirection = cosOfVectors < cos(angleInRadians) - angleTolerance;

            if (!isRightDirection) {

                if ( distanceBetweenObjects < sumOfSize ) {
                    float overlap = sumOfSize - distanceBetweenObjects;

                    character.position.x = character.position.x + -collisionNormalizedVector.x * overlap;
                    character.position.y = character.position.y + -collisionNormalizedVector.y * overlap;

                }
                directionVector = Vector2({ -directionVector.y, directionVector.x });

            }

        }
    }
```
## 📚 Useful Links
Raylib Documentation
vcpkg Documentation
###✨ Thank You
Thank you for visiting! If you liked the project, feel free to star ⭐ the repository and follow me for more updates!

