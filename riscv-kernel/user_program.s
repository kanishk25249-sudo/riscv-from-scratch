.section .user_program, "a"
.global _user_program_start
.global _user_program_end

_user_program_start:
.incbin "user_program.raw"
_user_program_end: