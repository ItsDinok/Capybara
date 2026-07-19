" Vim syntax file
" Language: Capybara
" Install:
"   mkdir -p ~/.vim/syntax ~/.vim/ftdetect
"   cp capybara.vim ~/.vim/syntax/
"   echo 'au BufRead,BufNewFile *.capy set filetype=capybara' > ~/.vim/ftdetect/capybara.vim
" (Neovim: use ~/.config/nvim/ instead of ~/.vim/)

if exists("b:current_syntax")
  finish
endif

" Keywords
syn keyword capyConditional if else
syn keyword capyRepeat while for
syn keyword capyStatement break continue return
syn keyword capyBoolean true false
syn keyword capyType string int float double bool void

" Identifiers ($ and _ allowed, per the lexer)
syn match capyIdentifier "\<[A-Za-z_$][A-Za-z0-9_$]*\>"

" Numbers (integer-only for now, matching the lexer)
syn match capyNumber "\<\d\+\>"

" Strings (no escapes yet, matching the lexer)
syn region capyString start=+"+ end=+"+

" Comment types — each gets its own group so you can colour them apart
syn match capyComment "//.*$"
syn match capyCommentBang "!!.*$"
syn match capyCommentQuery "??.*$"
syn match capyCommentArrow ">>.*$"
syn match capyCommentQBang "?!.*$"

" Operators
syn match capyOperator "[-+*/%=<>!]=\?"
syn match capyOperator "&&\|||\|++\|--"

" Default links (any colourscheme will pick these up)
hi def link capyConditional  Conditional
hi def link capyRepeat       Repeat
hi def link capyStatement    Statement
hi def link capyBoolean      Boolean
hi def link capyType         Type
hi def link capyNumber       Number
hi def link capyString       String
hi def link capyComment      Comment
hi def link capyCommentBang  Todo
hi def link capyCommentQuery SpecialComment
hi def link capyCommentArrow SpecialComment
hi def link capyCommentQBang Todo
hi def link capyOperator     Operator
hi def link capyIdentifier   Identifier

let b:current_syntax = "capybara"
