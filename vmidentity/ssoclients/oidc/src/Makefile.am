lib_LTLIBRARIES = libssooidc.la

libssooidc_la_SOURCES = \
    oidc_globals.c \
    oidc_client.c \
    oidc_server_metadata.c \
    oidc_token.c \
    oidc_id_token.c \
    oidc_access_token.c \
    oidc_token_success_response.c \
    oidc_error_response.c

libssooidc_la_CPPFLAGS = \
    -I$(top_srcdir)/vmidentity/ssoclients/common/include/ \
    -I$(top_srcdir)/vmidentity/ssoclients/common/include/public/ \
    -I$(top_srcdir)/vmidentity/ssoclients/oidc/include/public/

libssooidc_la_LIBADD = \
    @top_builddir@/vmidentity/ssoclients/common/src/libssocommon.la
