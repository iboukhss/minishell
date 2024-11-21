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

Definitions:

- **control operator:** A _token_ that performs a control function. It is a <newline> or one of the following: `|`, `||`, `&`, `&&`, `|&`, `;`, `;;`, `;&`, `;;&`, `(` or `)`.

- **metacharacter:** A character that, when unquoted, separates words. A metacharacter is a <space>, <tab>, <newline> or one of the following characters: `|`, `&`, `;`, `(`, `)`, `<` or `>`.

- **operator:** A _control operator_ or a _redirection operator_. Operators contain at least one unquoted _metacharacter_.

- **token:** A sequence of characters considered a single unit by the shell. It is either a _word_ or an _operator_.

- **word:** A sequence of characters treated as an unit by the shell. Words may not include unquoted _metacharacters_.

### [Shell Syntax](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Syntax)

The shell operation goes as follows:

1. Read the input from a file, a string supplied as an argument with `-c` or from the user's terminal.
2. Break the input into _words_ and _operators_, obeying quoting rules. These _tokens_ are separated by _metacharacters_.
3. Parse the _tokens_ into simple and compound commands.
4. Perform the various shell expansions, breaking the expanded _tokens_ into lists of filenames, commands and arguments.
5. Perform any necessary redirections and remove the redirection _operators_ and their operands from the argument list.
6. Execute the command.
7. Optionally wait for the command to complete and collect its exit status.

### [Shell Expansions](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Expansions)
### [Redirections](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Redirections)
### [Executing Commands](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Executing-Commands)
### [Shell Builtin Commands](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Builtin-Commands)
### [Shell Variables](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Variables)
### [Using History Facilities](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Using-History-Interactively)
See also: [GNU Readline](https://en.wikipedia.org/wiki/GNU_Readline)
