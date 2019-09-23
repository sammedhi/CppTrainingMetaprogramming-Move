This project is a simple training to c++ metaprogramming and move 
semantic and to get a better understanding of the SFINAE. I implemented 
a List container which allow you to put any 
kind of element and push it to the end . Trying to be as optimal the 
push function is an universal reference , and I overload the operator<< 
to allow to print the list :

```
std::cout << my_list ;
```

the function got two overload for pointer and not pointer type using 
SFINAE to discard the wrong implementation .

Once again this is just a training project . If you ever read this and 
have some question you can reach me at sammedhi2@hotmail.fr !
