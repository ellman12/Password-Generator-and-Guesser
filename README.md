# Password-Generator-and-Guesser
Slightly over-engineered password guesser program written in C++. There are a ton of different arguments you can pass to it to control how it operates. It also has the ability to display how long it took to guess the password. This was made for two reasons: to give me some C++ experience, and to get some experience working with command line arguments (flags). I'm not sure where I got the idea to make a password guesser like this.<br><br>

## Compile
Clone the repo and <code>cd</code> into the <code>src</code> folder<br>
Compile with this command:
<code>g++ -o "PGG.exe" PGG.cpp</code><br><br>

## Arguments
Control Password Generation<br>
\--------------------------------<br>
<code>-d</code> Use digits in the generated password<br>
<code>-l</code> Use lowercase a-z in the generated password<br>
<code>-u</code> Use uppercase A-Z in the generated password<br>
<code>-s</code> Use special characters in the generated password<br>
<code>-p</code> Input your own password after the -p. Causes d, l, u, and s to be set automatically<br>
<code>-L</code> Force the generated password to be a certain length<br>
<code>-M</code> If no length given, generate random length between 1 and M. 50 is default max length<br><br>

Control rand() Seed<br>
\---------------------<br>
<code>--noseed</code> Default srand value (same numbers generated every time)<br>
<code>--time</code> Use time(0) as the seed (default if neither specified)<br>
<code>-S\<digits></code> Custom seed value<br><br>

Control Password Guessing<br>
\------------------------------<br>
<code>--store     </code> (Default) Store guesses to avoid duplicating. This can also help make guessing faster<br>
<code>--nostore   </code> Don't store them. Can help avoid running out of memory if the password is long<br>
<code>--series    </code> A significantly better guessing algorithm. Goes through 1 char at a time to crack the password<br>
<code>--increment </code> Somewhat similar to --series. Starts at something like AAAAA, then goes to BAAAA, then CAAAA, etc.<br>
<code>-O"filename"</code> Output guessing function result to a file<br><br>

Misc<br>
\-----<br>
<code>--help</code> Displays the help thing. Also displayed when invalid/unknown flag specified<br>
<code>-v</code> (Verbose) Tells you what things happen under the hood and when. I recommend using this flag.<br>
<code>--noenter</code> Skip the 'Hit ENTER' thing that happens before guessing begins. Useful for testing and debugging and if you don't need to view the Verbose stuff.<br>
<code>--noprint</code> Don't print out current guess, number of guesses, etc. while guessing password. This causes guessing to be significantly faster.<br><br>

## Basic Examples
```
$ ./PGG.exe
```
Running with no arguments displays all the arguments shown above.<br><br>

```
$ ./PGG.exe -d
```
Creates a random password of random length consisting of all digits that the computer will guess using the default guessing method<br><br>

```
$ ./PGG.exe -l
```
Same as above but with lowercase<br><br>

```
$ ./PGG.exe -d -l -u -s
```
Create and guess random password with digits, upper and lower case characters, and special characters.<br><br>

```
$ ./PGG.exe -d -l -L30
```
Create and guess a 30 character password with digits and lowercase characters only.<br><br>

```
$ ./PGG.exe -d -l -u -M100
```
Create and guess a random password of random length 1–100 consisting of digits, lowercase, and uppercase.<br><br>

```
$ ./PGG.exe -p123abcABC!@#$
```
The -p flag is used to specify the password you want PGG to guess. If you want to use special characters in it like '&', '^', etc., you will most likely have to put the -p in quotes like this: ```"-p29sdhjgs^&%^&^^^%^%^3781278278"```<br><br>

```
$ ./PGG.exe -p4658764783248348939932489 --series
```
Guess this password using the very fast series method. This method goes through char-by-char and guesses and checks until that is the right char and continues until it reaches the end.<br><br>

```
$ ./PGG.exe -p29378127381238218738278 --increment
```
Guess this password using the also very fast increment method. This is similar to series but instead of randomly guessing and checking a char, it increments that char until it's right. E.g., if the password was AAAAAAAA, it would first try that, then BAAAAAAA, then CAAAAAAA, etc.<br><br>

## Advanced Examples
You can control the seed used for the rand() function.
```
$ ./PGG.exe --noseed
```
This causes the default seed for rand() to be used<br><br>

```
$ ./PGG.exe --time
```
Use time(0) as the seed. This is the default behavior and thus you don't need to specify this flag.<br><br>

```
$ ./PGG.exe -S12345678
```
Similar to -p. Specify the seed you want rand() to use.<br><br>
```
$ ./PGG.exe --nostore -p1234568347328478
```
By default, PGG stores guesses in a vector to avoid duplicating guesses. However, this is pretty inefficient and you can turn it off with the ```--nostore``` flag.<br><br>

```
$ ./PGG.exe -d -l -u -s --noprint
```
If you don't want PGG to print out stuff while it is guessing the password, pass in this argument.<br><br>

```
$ ./PGG.exe -p123456 -OHelloWorld
```
When PGG finally guesses the password, have it send the results to a file. You do not need to give it an extension in the -O flag.