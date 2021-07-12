# ever wanted your functions to be nicer?
with clerk you can write code like this:
```C++
auto query_server = clerk(simple_query_function);
query_server(ip_t =  "98.23.4.5");
...
query_server(query_t = "are there other function clerks?"s);
auto is_other_clerk = query_server();
auto is_cool = query_server(query_t = "is this cool?"s)();
...
query_server(ip_t = "34.25.6.1");
auto new_server_data = query_server(query_t = "hello new server"s);
```
