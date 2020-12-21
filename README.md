# C_my_Hash_Table
A hash table with dynamic size in C.

To create a hashing table you send a hashing method and an equals method as parameters, which the hash table will use in all of its internal functions. There are also some basic hashing methods in "basic_hash" that can be used.

# Hash Table Methods
Most methods receive the hash table as the first parameter, similar to self in python.

## Insert:
This method receives as parameters the hash table, the key, and the value to store and returns the position where it was stored(This position can change after an expantion). If there are too many elements in the position in which it is trying to insert this value, the hash table will expand. In case of error it will return -1.

## Remove:
This method receives as parameters the hash table, a key, and returns the value related to the given key. This method deletes the element of the hash table related to the given key. It will return null if there is no element related to that key.

## Value_of:
This method receives as parameters the hash table, a key, and returns the value related to the given key. It return null if there is no element related to that key

## Equals:
This methods receives as parameters two elements to compare, and returns a short int with the result of the comparison.

## Hash:
This methods receives as parameter one element and returns a long long, which is the related hash.

# Hash Table Propierties

## Keys
A pointer to void pointers in which the hash table keys are stored.

## Values
A pointer to the struct hash_t_elem that represents the hash table state.

## Count
An int that represents how many key, value pairs have been stored in the hash table.

## Size
An int that represents the size of the values as an array.

## Max Depth
An int that represents the maximun of elements that can be stored in one of the values positions.

# Creating the Hash Table
To Create a hash table call the method create_hash_table, which receives as parameters an int : Max Depth, a function : Hash, a function : Equals and return a pointer to a hash table. 

# How to use it in your C project
To be able to use it in your C projects you can either execute the command make and use the resulting dynamic libraries taking the header files and exporting the ld_path:
$export LD_LIBRARY_PATH=<Library_Path>:$LD_LIBRARY_PATH
And then linking the library, using gcc you can compile and link as follows:
$gcc -L<Library_Path> <To_compile> -l<library_name_without_lib_at_the_beginning_nor_.so_at_the_end>

Or you can also execute:
$./install.sh
And then linking the library, using gcc:
$gcc <To_compile> -l<library_name_without_lib_at_the_beginning_nor_.so_at_the_end>
