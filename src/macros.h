#pragma once
#define IMPL(prefix, namespace, func)  namespace->func = &prefix ## _ ## namespace ## _ ## func;
