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

** Anything not asked is not required **

## Useful ressources

- GNU Bash documentation: https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html
- UNIX processes playlist: https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY
- xv6 shell walkthrough: https://www.youtube.com/watch?v=ubt-UjcQUYg
