<h1>September 10:<h1>
Began planning everything, idea is c++ backend and some sort of web app as a display.
Writing a Vector library in order to refamiliarize myself with c++ basics

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

<h1>September 11:<h1>
Finished up the big 5 on entity class. Started the rigidbody class, still deciding what should be included
    - Restitution: How 'bouncy' an object is, or how elastic. 0 -> inelastic, 1 -> elastic (no energy loss)
    