Shrinks path given by first argument.

### Usage
```
shrink-path ~/foo/bar/baz
dirs -p | shrink-path
```

| before | after |
| -- | -- |
| ~/foo/bar/baz | ~/f/b/baz |
| ~named/foo/bar | ~named/f/bar |
| ~ | ~ |
| ~/.config/zsh | ~/.c/zsh |
