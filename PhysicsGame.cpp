#include <iostream>
#include <raylib.h>
#include <math.h>
#include <cmath>
#include <vector>

using namespace std;

class GameObject {
public:
    Vector2 position;
    vector<GameObject*> collisions;
    float size;
};

class Character: public GameObject {
public:
    float speed;
};

class CustomCircle : public GameObject {
};

float getModuleOfVector  (Vector2 vector){
    return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}


Vector2 getNormalizedVector(Vector2 firstPoint, Vector2 secondPoint) {
    Vector2 computedVector = { secondPoint.x - firstPoint.x, secondPoint.y - firstPoint.y };
    float computedVectorModule = getModuleOfVector(computedVector);

    if (computedVectorModule < 0.01f) {
        return Vector2{ 0, 0 };
    }

    Vector2 normalizedVector = { computedVector.x / computedVectorModule, computedVector.y / computedVectorModule };
    return normalizedVector;
}

Vector2 getDirectionVector(GameObject gameObject) {

    Vector2 directionVector = gameObject.position;

    if (IsKeyDown(KEY_RIGHT)) {
        //cout << "Right Key" << "\n";
        directionVector = { directionVector.x + 1, directionVector.y };
    }
    if (IsKeyDown(KEY_LEFT)) {
        //cout << "LEFT Key" << "\n";
        directionVector = { directionVector.x - 1, directionVector.y };
    }
    if (IsKeyDown(KEY_UP)) {
        //cout << "Up Key" << "\n";

        directionVector = { directionVector.x, directionVector.y - 1 };
    }
    if (IsKeyDown(KEY_DOWN)) {
        //cout << "Down Key" << "\n";
        directionVector = { directionVector.x, directionVector.y + 1 };
    }
    return getNormalizedVector(gameObject.position, directionVector);
}

void drawCharacter(Character& character) {
    float deltaTime = GetFrameTime();
    float calculatedSpeed = fmin(character.speed * deltaTime, 50.0f);
   
    Vector2 directionVector = getDirectionVector(character);

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



    character.position.x = character.position.x + directionVector.x * calculatedSpeed;
    character.position.y = character.position.y + directionVector.y * calculatedSpeed;
    DrawCircle(character.position.x, character.position.y, character.size, RED);
    DrawLine(character.position.x, character.position.y, character.position.x + directionVector.x * 20.f, character.position.y + directionVector.y * 20.0f, BLACK);
}




void checkCollision(GameObject& firstObject, GameObject& secondObject) {
    float minDistanceCollision = 0.1f;
    Vector2 firstObjectRay = getNormalizedVector(firstObject.position, secondObject.position);

    Vector2 firstObjectCollisionVector = { firstObject.position.x + firstObject.size * firstObjectRay.x , firstObject.position.y + firstObject.size * firstObjectRay.y };
    Vector2 secondObjectCollisionVector = { secondObject.position.x + secondObject.size * -firstObjectRay.x , secondObject.position.y + secondObject.size * -firstObjectRay.y };

    Vector2 distanceVector = { secondObjectCollisionVector.x - firstObjectCollisionVector.x, secondObjectCollisionVector.y - firstObjectCollisionVector.y };
    float moduleOfDistanceVector = getModuleOfVector(distanceVector);

    /*Vector2  vectorBetweenCircles = { secondObject.position.x - firstObject.position.x, secondObject.position.y - firstObject.position.y };
    float distanceBetweenCircles = getModuleOfVector(vectorBetweenCircles);*/

    if (moduleOfDistanceVector < minDistanceCollision) {
        if (find(firstObject.collisions.begin(), firstObject.collisions.end(), &secondObject) == firstObject.collisions.end()) {
            firstObject.collisions.push_back(&secondObject);
        }
    }
    else {
        auto it = find(firstObject.collisions.begin(), firstObject.collisions.end(), &secondObject);
        if (it != firstObject.collisions.end()) {
            firstObject.collisions.erase(it);
        }
    }
}

int main()
{
	int windowWidth = 800;
	int windowHeight = 600;

    Character mainCharacter;
    mainCharacter.position = Vector2({ 300, 360 });
    mainCharacter.size = 20;
    mainCharacter.speed = 200.0f;

    CustomCircle circle;

    circle.position = Vector2({ 300, 300 });
    circle.size = 40;

        

	InitWindow(windowWidth, windowHeight, "Physics test");

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);


        checkCollision(mainCharacter, circle);
        DrawCircle(circle.position.x, circle.position.y, circle.size, BLUE);
        drawCharacter(mainCharacter);

        EndDrawing();
    }


    CloseWindow();
}

