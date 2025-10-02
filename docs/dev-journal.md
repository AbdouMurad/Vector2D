<h1>September 10:
<h4>
Began planning everything, idea is c++ backend and some sort of web app as a display.
Writing a Vector library in order to refamiliarize myself with c++ basics.

Creating entity class, planning inheritance hierchy
Entity -> RigidBody, RigidBody should have a shape as a component. 
Entity class is first time I use the big 5:
- Destructor
- Copy Constructor
    - 1 param -> lvalue reference to same type
    - By default a copy constructor is included
    - Will copy all values -> problem is it copies all references 
    - ex: 
    List l2 = l1;
    //compiler attemps to create l2 with values of l1, including addresses found in l1
    - Copy Constructor:
        List(const List &l);
- Copy Assignment Operator
    - Similar to copy constructor, instead of 
    List l2 = l1; 
    its
    l2 = l1
    - copy by val but same thing for addresses -> causes double free when destructed
- Move Operations and RValues
    - When we pass a l-value we don't to pass by value because then it will create and delete an object at the begining and end of every call - wasteful
    - We can use an r-value reference, which allows us to pass the object by reference instead of copying
    - We create a move constructor:
        class List {
            public:
            ...
            List(List &&o) : theHead{o.theHead}, len{o.len} {
                o.theHead = nullptr;
                o.len = 0;
            }
            List &operation(List &o) {
                swap(0); //by swapping the data, we make the r-value destructor to free the data we don't need anymore and keep the data we want copied
            }
        };
- Move and Copy Elision
    - Look it up if needed -> compiler setting we can turn off

<h1>September 11:
<h4>
Finished up the big 5 on entity class. Started the rigidbody class, still deciding what should be included

- Restitution: How 'bouncy' an object is, or how elastic. 0 -> inelastic, 1 -> elastic (no energy loss)
Realized that storing vectors in RigidBody using pointers was hindering performance, vector is not a big enough class that it can't be passed by value. Much faster to create onto stack
- Removal of this led to the removal of a lot of the code written for the big 5 
-> feels like a step back but is a performance boost and better for safety

Created Shape class, will act as parent class to multiple shapes. For now I think I will have rectangle and circle. 
How this works is we can still attach each shape by the pointer of the parent class shape. This is because under the hood the memory still begins with the memory of shape, then it is extended by the child class. So you can think of this as Shape and Circle for example will both share the same address to the begining beacuse Circle is just an extension of shape.
- I want to give the user the option to create a rigid body without a collider, (might be useful to simulate singular points or what not).
    - Tricky part is dealing with lifetime. If we create the shape in main funciton and attach then it doesn't belong to the rigid body and will delete once the stackframe on main closes. Solution to this is use unique_ptr
        - Unique_ptr acts just like a ptr but with extra steps. It ensures that it only has one owner, (no move or copy constructor). No need for new or delete as it lives as long as stack frame does -> belongs to the lifespan of the rb object

<h1>September 15
<h4>
Created functionality to print rigid body (only works for circle colldier). I had to work backwords and create the overload operators for the lowest classes first like the circle class. 

Interesting part is since the collider in the rigid body class is 
defined as a unique pointer to a shape, it expects the operator that takes shape as a param. The work around this was create a virtual function for the circle called print, which manipulated the stream opperand. 

This way we can overlaod the shape << operator and from within it call the ovveriden print function. 
- I still need to implement the functionality for rectangles
- Need to clean up my code, starting to look messy
- Need to figure out a consistent format for printing object attributes
- Implement the logic to update the moment of inertia after the collider is added

<h1> September 16
<h4>
Finished up the << operator for printing the rigidbody object. 
Along with that I implemented the Rectangle shape class.

I also created a set collider method so the user has the option to create a rigidbody without a collider to begin with. Along with that I now call the compute moment of inertia method whenever a  collider is attached. 

To Do:
- Research the next step -> am I ready to apply forces?
- Look over collision algorithm from archived project -> how would shapes of different types interact? ex. Circle colliding with a rectangle.

Started the physcis manager script which includes the world class which will hold all objects and forces.

Researched how to implement time -> using chrono library
Implemented Vector library instead of custom list class -> much more optimized 

<h1>September 17
<h4>
1 Week MARK!


Created the update loop, every time the duration passes the dt set, we call the update function in the World class. Setup a start function as well thats called once. Just like how Unity and UE work. 

Implemented globalAccelration -> better than globalForce because if we look at gravity as an example every body has its own force but they share an accelration.
Rigidbodies now have a forces vector which tracks what forces are being applied at every frame. 
- Frame Begins -> forces = 0
- Apply global accelerations to forces
- Apply any seperate forces acting on object
- Call integrate function -> converts forces to acceleration -> integrates acceleration into velocity and velocity into position based on dt.
- Set forces = 0, repeat

TODO:
- Watch The Cherno series on making a game enigne
- Start looking over collision algorithms
- Code still needs cleaning up -> Will have a hard time reading it a month from now


<h1>September 30
<h4>
Source for seperate axis theorem: https://www.youtube.com/watch?v=dn0hUgsok9M

How the seperate axis theorem works is we look at the line that 2 points make for each shape (a rectangle has 4 different axis to check) -> project each corner onto the line of both shape and see if there is a overlap

- Implemented SAT for rectangle x rectangle
<h4>
SAT works by projecting corners of the object onto an axis and then we can easily look at the overlap to determine if there is a possible collision or not
<h4>
- If atleast 1 axis shows that there is no collision then the objects are apart and not colliding

TODO:
    Implement logic for circle x rectangle (circle x circle already done - very simple)

<h1>October 1
<h4>
Implemented logic for circle x rectangle - a bit more difficult

The same exact process but with axis from rectangle plus an extra axis from circle to point on rectangle closest to circle
 - This point is found by clamping the coords of the circle with rect +- the half width/height
 - For rotated rects its a bit harder -> find location of circle with respect to rect -> rotate coords so its on the same axis as rect -> find point -> unrotate point

TODO: 
 - Further test with Unity 2D world -> create a circle and a rect and see result of collision detection
 - Find out how to deal with collisions. Do I have to push the pieces apart? how do I apply forces? In what direction?
 - Implement box colliders as a soft check to see if objects are close enough to check collision