# Minishell

## TODO

Initial goals:

- Learn as much information as possible about the subject
  - Use GNU Bash as reference
  - Understand processes, signals, fork, pipe, ect.
  - Find ideas for parsing
- Establish the project goals clearly (important!)
- Agree upon rules to make collaboration easy (git flow? trunk based?)
- Divide the work (parsing? execution?)
- Lay down a solid fundation to build upon
- Schedule regular (weekly?) check-ins to review progress

Things to keep in mind:

- Make sure to stay in sync even when working on different parts of the code, i.e., try to understand the codebase as a whole
- Make sure to test the code as much as possible
- Focus on making it work, then making it right

Things to avoid:

- Don't get blackholed

## Feature list

- [ ] Display a prompt
- [ ] Have a working history
- [ ] Search and launch the right executable based on PATH (or absolute path)
- [ ] Do not interpret unclosed quotes, backslashes or semicolons
- [ ] Handle single quotes: `'example'`
- [ ] Handle double quotes: `"example"`
- [ ] Implement redirections: `<`, `>`, `<<`, `>>`
- [ ] Implement pipes: `|`
- [ ] Handle environment variables: `$FOO`
- [ ] Handle `$?`
- [ ] Handle `Ctrl-C`, `Ctrl-D` and `Ctrl-\`
- [ ] Implement builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

**Anything not asked is not required**

## Useful ressources

- GNU Bash documentation: https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html
- GNU Bash source repository: https://git.savannah.gnu.org/cgit/bash.git/tree/
- UNIX processes playlist: https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY
- xv6 shell walkthrough: https://www.youtube.com/watch?v=ubt-UjcQUYg

## Relevant sections of Bash manual for minishell

### [Definitions](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Definitions)

#### control operator
A _token_ that performs a control function. It is a `newline` or one of the following: `|`, `||`, `&`, `&&`, `|&`, `;`, `;;`, `;&`, `;;&`, `(` or `)`.

#### metacharacter
A character that, when unquoted, separates words. A metacharacter is a `space`, `tab`, `newline` or one of the following characters: `|`, `&`, `;`, `(`, `)`, `<` or `>`.

#### operator
A _control operator_ or a _redirection operator_. Operators contain at least one unquoted _metacharacter_.

#### token
A sequence of characters considered a single unit by the shell. It is either a _word_ or an _operator_.

#### word
A sequence of characters treated as an unit by the shell. Words may not include unquoted _metacharacters_.

### [Shell Syntax](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Syntax)

The shell operation goes as follows:

1. Read the input from a file, a string supplied as an argument with `-c` or from the user's terminal.
2. Break the input into _words_ and _operators_, obeying quoting rules. These _tokens_ are separated by _metacharacters_.
3. Parse the _tokens_ into simple and compound commands.
4. Perform the various shell expansions, breaking the expanded _tokens_ into lists of filenames, commands and arguments.
5. Perform any necessary redirections and remove the _redirection operators_ and their operands from the argument list.
6. Execute the command.
7. Optionally wait for the command to complete and collect its exit status.

Quoting:

Quoting is used to remove the special meaning of sertain characters or _words_ to the shell. Quoting can be used to disable special treatment for special characters, to prevent reserved words from being recognized as such, and to prevent parameter expansion.

Each of the shell _metacharacters_ has special meaning to the shell and must be quoted if it is to represent itself.

#### Single quotes
Enclosing characters in single quotes preserves the literal value of each character within the quotes. A single quote may not occur between single quotes, even when preceded by a backslash.

#### Double quotes
Enclosing characters in double quotes preserves the literal value of all characters within the quotes, with the exception of `$`, `` ` ``, `\` and, when history is enabled `!`.

### [Shell Commands](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Commands)

Check the sections for "Simple Commands", "Pipelines" and "List of Commands" (bonus part only).

### [Shell Expansions](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Expansions)

Mostly relevant for implementing shell variables (is it even necessary?).

### [Redirections](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Redirections)

TODO.

### [Executing Commands](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Executing-Commands)

Simple command expansion:

When a simple command is executed, the shell performs the following expansions, assignments, and redirections, from left to right, in the following order.

1. The _words_ that the parser has marked as variable assignments and redirections are saved for later processing.
2. The _words_ that are not variable assignments or redirections are expanded. If any _words_ remain after expansion, the first _word_ is taken to be the name of the command and the remaining _words_ are the arguments.
3. Redirections are performed.
4. The text after the `=` in each variable assignment undergoes tilde expansion, parameter expansion, command expansion, arithmetic expansion and quote removal before being assigned to the variable.

Command search and execution:

After a command has been split into words, if it results in a simple command and an optional list of arguments, the following actions are taken.

1. If the command name contains no slashes, the shell attempts to locate it. If there exists a shell function by that name, that function is invoked.
2. If the name does not match a function, the shell searches for it in the list of shell builtins. If a match is found, that builtin is invoked.
3. If the name is neither a shell function nor a builtin, and contains no slashes, Bash searches each element of `$PATH` for a directory containing an executable file by that name. If the search is unsuccessful, the shell searches for a function named `command_not_found_handle`. If that function exists, it is invoked in a separate execution environment with the original command and its arguments, and the function exit status becomes the exit status of that subshell. If that function is not defined, the shell prints an error message and returns an exit status of 127.
4. If the search is successful, or if the command name contains one or more slashes, the shell executes the named program in a separate execution environment. Argument 0 is set to the name given, and the remaining arguments to the command are set to the arguments supplied, if any.
5. If this execution fails because the file is not in executable format, and the file is not a directory, it is assumed to be a shell script and the shell executes it.
6. If the command was not begun asynchronously, the shell waits for the command to complete and collects its exit status.

### [Shell Builtin Commands](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Builtin-Commands)

#### cd
Change the current working directory to _directory_. If _directory_ is not supplied, the value of the `HOME` shell variable is used.  
If `..` appears in _directory_, it is processed by removing the immediatly preceding pathname component, back to a slash or the begining of _directory_.  
If _directory_ is `-`, it is converted to `$OLDPWD` before the directory change is attempted.  
If the directory change is successful, `cd` sets the value of the `PWD` environment variable to the new directory name, and sets the `OLDPWD` environmnent variable to the value of the current working directory before the change.  
The return status is zero if the directory is successfully changed, non-zero otherwise.

#### echo
TODO.

#### env
TODO.

#### exit
Exit the shell, returning a status of _n_ to the shell's parent. If _n_ is ommited, the exit status is that of the last command executed. Any trap on _EXIT_ is executed before the shell terminates.

#### export
Mark each _name_ to be passed to child processes in the envirnonment.  
If the `-f` option is supplied, the _names_ refer to shell functions; otherwise the names refer to shell variables. The `-n` option means to no longer mark each _name_ for export.  
If no _names_ are supplied, or if the `-p` option is given, a list of all exported variables is displayed. The `-p` option displays output in a form that may be reused as input. If a variable name is followed by `=value`, the value of the variable is set to _value_.  
The return status is zero unless an invalid option is supplied, one of the names is not a valid shell variable, or `-f` is supplied with a name that is not a shell function.

#### pwd
Prints the absolute pathname of the current working directory. If the `-P` option is supplied, the pathname printed will not contain symbolic links. If the `-L` option is supplied, the pathname printed may contain symbolic links. The return status is zero unless an error is encountered while deteremining the name of the current directory or an invalid option is supplied.

#### unset
Remove each variable of function _name_. If the `-v` option is given, each _name_ refers to a shell variable and that variable is removed. If the `-f` option is given, the _names_ refer to shell functions, and the function definition is removed. If the `-n` option is supplied, and _name_ is a variable with the `nameref` attribute, _name_ will be unset rather than the variable it references.  
`-n` has no effect if the `-f` option is supplied. If no options are supplied, each _name_ refers to a variable; if there is no variable by that name, a function with that name, if any, is unset.  
Readonly variables and functions may not be unset. Some shell variables lose their special behavior if they are unset; such behavior is noted in the description of individual variables.  
The return status is zero unless a _name_ is a readonly or may not be unset.


### [Shell Variables](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Variables)
### [Using History Facilities](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Using-History-Interactively)
See also: [GNU Readline](https://en.wikipedia.org/wiki/GNU_Readline)
