Shrinks path given by first argument.

### Usage
```
shrink-path ~/foo/bar/baz
shrink-path "$(dirs -p | head -n1)"
```

| before | after |
| -- | -- |
| ~/foo/bar/baz | ~/f/b/baz |
| ~named/foo/bar | ~named/f/bar |
| ~ | ~ |
| ~/.config/zsh | ~/.c/zsh |
