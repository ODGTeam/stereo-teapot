#include <android_native_app_glue.h>
#ifndef _OSTERHOUTGROUP_EXT_H
#define _OSTERHOUTGROUP_EXT_H

#ifdef __cplusplus
extern "C" {
#endif

//void extend_display(ANativeActivity* activity, bool extend);
void extend_display(android_app* state, bool extend);

#ifdef __cplusplus
};
#endif


#endif /* _OSTERHOUTGROUP_EXT_H */
