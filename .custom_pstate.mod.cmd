savedcmd_custom_pstate.mod := printf '%s\n'   custom_pstate.o | awk '!x[$$0]++ { print("./"$$0) }' > custom_pstate.mod
