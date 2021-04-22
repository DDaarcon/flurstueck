# flurstueck
### Setting up
To compile program, in its directory run command
```
g++ main.cpp -o flurstueck
```
and then (on Linux)
```
./flurstueck.out file_type file_name
```
(on Windows)
```
flurstueck file_type file_name
```
### Information
Program uses RapidXML C++ library.
Application purpose is to get data from correctly formated xml files and print it on screen.
Now it supports aaa and nas formats.
### Extending by new formats
To include support of new format:
- in includes/finders.hpp create new class derived from FinderBase, where in constructor you input paths for nodes you want to print (similarly to how it looks in FinderAAA and FinderNAS)
- in main.cpp, function main, add next _else if_:
```
else if (fileFormat == "your_format") {
  YourFinder finder;
  values = finder.FindValues(&document);
}
```
