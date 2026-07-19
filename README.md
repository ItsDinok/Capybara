# Capybara
### A Friendly Programming Language

Capybara is a statically typed compiled programming language designed to make systems-level development less verbose and much friendlier. It has a simple package manager, C/C++ compatibility, native executables, and opinions that are designed to make the language easier to use, not to force a certain style.

### Quirks

Capybara was designed to maximise readability, editability, and give the developer more tools to make their code approachable and maintainable. The three biggest innovations are:

- Native special variable highlighting, demarcated by `$`
- Multiple comment types for fast navigation 
- Comment emission by compiler to keep you in the loop `>> comment`

### Example Code

```
// This is a normal comment
?? This is an explanatory comment
!! This is a todo/bug marker
?! This comment explains dense/obscure code
>> This comment can be emitted by the compiler {TIME_COMPILE} {COMPILE_THREAD}
graze package.capy;

int main() {
    string x = "Hello";
    chirp(x);

    if (x == "yes") {
      do something...
    }
    else do something else;
}
```
