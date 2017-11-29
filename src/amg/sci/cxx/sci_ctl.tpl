[+ AutoGen5 template +]
[+ (set-writable (not R_OK)) +]
[+
#
+]
[+ # Create hxx. +]
[+ (out-push-new "amg_sci_ctl.hxx") +]
[+ INCLUDE "sci_ctl.hxx" +]
[+ (out-pop) +][+ # Create hxx. +]
[+
#
+]
[+ # Create cxx. +]
[+ (out-push-new "amg_sci_ctl.cxx") +]
[+ INCLUDE "sci_ctl.cxx" +]
[+ (out-pop) +][+ # Create hxx. +]