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
- Move and Copy Elision