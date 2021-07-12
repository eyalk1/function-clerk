# ever wanted your functions to be nicer?
with clerk you can write code like this:
```C++
auto query_server = clerk(simple_query_function);
query_server(ip =  "98.23.4.5"); //set the ip argument of this function
...
query_server(query = "are there other function clerks?"s); //set the query argument of this function
auto is_other_clerk = query_server(); // run the function
query_server(query = "is this cool?"s); //update the query.
auto is_cool = query_server(); // run the function
...
query_server(ip = "34.25.6.1");
auto new_server_data = query_server(query_t = "hello new server"s)();
```

With clerk you can talk to your functions!
Some of the features:
1. input arguments in any order you'd like
2. change arguments after inputing them
3. change the funtion to call
4. ask for the state of the values given

The parameters of the given function must all be different - therefor this project work best with joboccara's NamedType - https://github.com/joboccara/NamedType
