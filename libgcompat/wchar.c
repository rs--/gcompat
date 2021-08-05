#include <assert.h> /* assert */
#include <stdarg.h> /* va_list, va_start, va_end */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* abort */
#include <wchar.h>  /* wchar_t, *wprintf */

int __vswprintf_chk(wchar_t *s, size_t n, int flag, size_t slen,
                    const wchar_t *format, va_list ap);
int __vfwprintf_chk(FILE *fp, int flag, const wchar_t *format, va_list ap);

/**
 * Convert formatted wide-character output, with stack checking
 *
 * LSB 5.0: LSB-Core-generic/baselib---fwprintf-chk-1.html
 */
int __fwprintf_chk(FILE *stream, int flag, const wchar_t *format, ...)
{
	int ret;
	va_list ap;

	va_start(ap, format);
	ret = __vfwprintf_chk(stream, flag, format, ap);
	va_end(ap);

	return ret;
}

/**
 * Convert formatted wide-character output, with stack checking
 *
 * LSB 5.0: LSB-Core-generic/baselib---vfwprintf-chk-1.html
 */
int __vfwprintf_chk(FILE *fp, int flag, const wchar_t *format, va_list ap)
{
	assert(fp != NULL);
	assert(format != NULL);

	return vfwprintf(fp, format, ap);
}

/**
 * Convert formatted wide-character output, with stack checking
 *
 * LSB 5.0: LSB-Core-generic/baselib---swprintf-chk-1.html
 */
int __swprintf_chk(wchar_t *s, size_t n, int flag, size_t slen,
                   const wchar_t *format, ...)
{
	int ret;
	va_list ap;

	va_start(ap, format);
	ret = __vswprintf_chk(s, n, flag, slen, format, ap);
	va_end(ap);

	return ret;
}

/**
 * Convert formatted wide-character output, with stack checking
 *
 * LSB 5.0: LSB-Core-generic/baselib---vswprintf-chk-1.html
 */
int __vswprintf_chk(wchar_t *s, size_t n, int flag, size_t slen,
                    const wchar_t *format, va_list ap)
{
	assert(s != NULL || n == 0);
	assert(slen >= n);
	assert(format != NULL);

	return vswprintf(s, n, format, ap);
}

/**
 * Copy a wide-character string, with buffer overflow checking
 *
 * LSB 5.0: LSB-Core-generic/baselib---wcscpy-chk-1.html
 */
wchar_t *__wcscpy_chk(wchar_t *dest, const wchar_t *src, size_t n)
{
	size_t srclen;

	assert(dest != NULL);
	assert(src != NULL);
	srclen = wcslen(src) + 1;
	assert(n >= srclen);
	if (dest < src) {
		assert(dest + n <= src);
	} else {
		assert(src + n <= dest);
	}

	return wcscpy(dest, src);
}

/**
 * Representation of the glibc internals of wcstol(3).
 *
 * LSB 5.0: LSB-Core-generic/baselib---wcstol-internal-1.html
 */
long int __wcstol_internal(const wchar_t *nptr, wchar_t **endptr, int base,
                           int group)
{
	assert(group == 0);
	return wcstol(nptr, endptr, base);
}

/**
 * Convert a wide-character string to an unsigned long int.
 *
 * Some day, when musl supports LC_NUMERIC, we can probably remove this.
 */
unsigned long int wcstoul_l(const wchar_t *nptr, wchar_t **endptr,
                            int base, locale_t loc)
{
	return wcstoul(nptr, endptr, base);
}

/**
 * Convert a wide-character string to a long int.
 *
 * Some day, when musl supports LC_NUMERIC, we can probably remove this.
 */
long int wcstol_l(const wchar_t *nptr, wchar_t **endptr, int base,
                  locale_t loc)
{
	return wcstol(nptr, endptr, base);
}

/**
 * Convert a wide-character string to a double.
 *
 * Some day, when musl supports LC_NUMERIC, we can probably remove this.
 */
double wcstod_l(const wchar_t *nptr, wchar_t **endptr, locale_t loc)
{
	return wcstod(nptr, endptr);
}

/**
 * Concatenate two wide-character strings, with buffer overflow checking.
 */
wchar_t * __wcscat_chk(wchar_t *dest, const wchar_t *src, size_t len)
{
    wchar_t *tmp1 = dest;
    const wchar_t *tmp2 = src;
    wchar_t c;

    /* Move to the end of the dest. Abort if it's too short  */
    do
    {
        if (len-- == 0)
            abort();
        c = *tmp1++;
    }
    while (c != L'\0');

    /* Append characters in src to the dest. Abort if it's too short  */
    do
    {
        if (len-- == 0)
            abort();
        c = *tmp2++;
        *tmp1++ = c;
    }
    while (c != L'\0');

    return dest;
}

/**
 * Copy a fixed-size string of wide characters, with buffer overflow checking.
 */
wchar_t * __wcsncpy(wchar_t *dest, const wchar_t *src, size_t len)
{
    wchar_t *tmp1 = dest;
    const wchar_t *tmp2 = src;
    wchar_t c = *src;

    for (size_t i = 0; i < len; i++)
    {
        /* If src has reached the null terminator, don't advance! */
        c = (c == L'\0') ? c : *tmp2++;
        *tmp1++ = c;
    }

    return dest;
}

/**
 * Concatenate two wide-character strings, with buffer overflow checking.
 */
wchar_t* __wcsncpy_chk(wchar_t *dest, const wchar_t *src, size_t n1, size_t n2)
{
    if (n2 < n1)
        abort();

    return __wcsncpy(dest, src, n1);
}