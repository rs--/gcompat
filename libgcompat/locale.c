#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "internal.h"

void *__newlocale(int, const char *, void *);
void __freelocale(void *);

struct glibc_locale {
	/* hopefully nobody pokes at this */
	void *__locales[13];

	const unsigned short int *__ctype_b;
	const int *__ctype_tolower;
	const int *__ctype_toupper;

	const char *__names[13];
};

const unsigned short **__ctype_b_loc(void);
const int32_t **__ctype_tolower_loc(void);
const int32_t **__ctype_toupper_loc(void);

const char *__gcompat_valid_locales[] = {"C", "POSIX"};

bool _is_valid_locale(const char *candidate) {
	for(int i = 0; i < sizeof __gcompat_valid_locales; i++) {
		if(strcmp(candidate, __gcompat_valid_locales[i]) == 0) return true;
	}
	return false;
}

struct glibc_locale *newlocale(int mask, const char *name, locale_t base) {
	GCOMPAT__assert_with_reason(_is_valid_locale(name),
			"locale %s not supported\n", name);
	struct glibc_locale *ret = malloc(sizeof(struct glibc_locale));
	if(ret == NULL) return NULL;

	ret->__locales[0] = __newlocale(mask, name, base);
	for(int l = 1; l < 13; l++) ret->__locales[l] = ret->__locales[0];
	ret->__ctype_b = *__ctype_b_loc();
	ret->__ctype_tolower = *__ctype_tolower_loc();
	ret->__ctype_toupper = *__ctype_toupper_loc();

	ret->__names[0] = strdup("C");
	for(int i = 1; i < 13; i++) ret->__names[i] = ret->__names[0];

	return ret;
}
