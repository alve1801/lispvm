# lispvm
RISC-ish VM for messing around with Lisp machines

Note: development merged into [QWAK](https://github.com/alve1801/qwaklisp), go there for updates and stuff

Expanded a lot on my [lisp interpreter](https://github.com/alve1801/lisp), wrote an [article](https://avethenoul.neocities.org/lisp) (haven't updated the github repo yet, but also I'm not done updating the interpreter either, so).

Next logical step was to write a bare-metal self-hosting Lisp environment. Instead of compiling to native machine code, I decided to split the difference by having a [hack-like](https://github.com/alve1801/hack) intermediary. Whipped one up yesterday, spent most of today hand-writing machine code to make it compute the Ackermann function. Posting it here, hopefully will update as I write more stuff for it.
