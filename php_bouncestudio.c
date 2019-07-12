/**
 * bounceStudio class
 *
 * @company Infolook, Avaaz.org
 * @author Gilbert Groenendijk <gilbert.groenendijk@infolook.nl>, Alexey Scherbakov <alexey.scherbakov@avaaz.org>
 * @copyright BoogieTools, Inc. 2006, Avaaz.org 2019
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_bouncestudio.h"

zend_class_entry *php_bouncestudio_entry;

PHP_FUNCTION(bounceStudio_DoBounceCheck)
{
    zval *self = getThis();
    zval *rawMessageBuffer, *ignoreAddresses, *licenseKey;
    char *bouncedEmailAddress;

    int bounceCode;
    if ((rawMessageBuffer = zend_hash_str_find(Z_OBJPROP_P(self), "RawMessageBuffer", sizeof("RawMessageBuffer") - 1)) == NULL) {
        zend_error(E_WARNING, "RawMessageBuffer wasn't set");
        RETURN_NULL();
    }

    ignoreAddresses = zend_hash_str_find(Z_OBJPROP_P(self), "IgnoreAddresses", sizeof("IgnoreAddresses") - 1);
    licenseKey = zend_hash_str_find(Z_OBJPROP_P(self), "LicenseKey", sizeof("LicenseKey") - 1);

    /* Do Check */
    bounceCode = bsBounceCheck(Z_STRVAL_P(rawMessageBuffer), &bouncedEmailAddress, Z_STRVAL_P(ignoreAddresses), Z_STRVAL_P(licenseKey));

    /* Add to an property */
    add_property_string(self, "BouncedEmailAddress", bouncedEmailAddress);

    RETURN_LONG(bounceCode);
}

PHP_FUNCTION(bounceStudio_GetCustomHeader) 
{
    zval *self = getThis();
    zend_string *customHeaderName;
    
    char *customHeaderValue;
    zval *rawMessageBuffer;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S",  &customHeaderName) == FAILURE)  {
        return;
    }

    if ((rawMessageBuffer = zend_hash_str_find(Z_OBJPROP_P(self), "RawMessageBuffer", sizeof("RawMessageBuffer") - 1)) == NULL) {
        zend_error(E_WARNING, "RawMessageBuffer wasn't set");
        RETURN_NULL();
    }

    bsGetCustomHeader(Z_STRVAL_P(rawMessageBuffer), &customHeaderValue, customHeaderName->val);

    RETURN_STRING(customHeaderValue);
}

PHP_FUNCTION(bounceStudio_GetCustomHeaderOriginalMessage)
{
    zval *self = getThis();
    zend_string *customHeaderName;
    char *customHeaderValue;
    zval *rawMessageBuffer;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S",  &customHeaderName) == FAILURE)  {
        return;
    }

    if ((rawMessageBuffer = zend_hash_str_find(Z_OBJPROP_P(self), "RawMessageBuffer", sizeof("RawMessageBuffer") - 1)) == NULL) {
        zend_error(E_WARNING, "RawMessageBuffer wasn't set");
        RETURN_NULL();
    }

    bsGetOrigCustomHeader(Z_STRVAL_P(rawMessageBuffer), &customHeaderValue, customHeaderName->val);

    RETURN_STRING(customHeaderValue);
}

PHP_FUNCTION(bounceStudio_MessageBody)
{
    zval *self = getThis();
    char *messageBody;
    zval *rawMessageBuffer;

    if ((rawMessageBuffer = zend_hash_str_find(Z_OBJPROP_P(self), "RawMessageBuffer", sizeof("RawMessageBuffer") - 1)) == NULL) {
        zend_error(E_WARNING, "RawMessageBuffer wasn't set");
        RETURN_NULL();
    }

    /* Retrieve the body */
    bsGetBody(Z_STRVAL_P(rawMessageBuffer), &messageBody);
    RETURN_STRING(messageBody);
}

PHP_FUNCTION(bounceStudio_MessageFromAddress)
{
    zval *self = getThis();
    char *fromAddress;
    zval *rawMessageBuffer;

    if ((rawMessageBuffer = zend_hash_str_find(Z_OBJPROP_P(self), "RawMessageBuffer", sizeof("RawMessageBuffer") - 1)) == NULL) {
        zend_error(E_WARNING, "RawMessageBuffer wasn't set");
        RETURN_NULL();
    }

    /* Retrieve the Message From Address */
    bsGetFromAddress(Z_STRVAL_P(rawMessageBuffer), &fromAddress);
    RETURN_STRING(fromAddress);
}

PHP_FUNCTION(bounceStudio_MessageFromFriendlyName)
{
    zval *self = getThis();
    char *fromFriendlyName;
    zval *rawMessageBuffer;

    if ((rawMessageBuffer = zend_hash_str_find(Z_OBJPROP_P(self), "RawMessageBuffer", sizeof("RawMessageBuffer") - 1)) == NULL) {
        zend_error(E_WARNING, "RawMessageBuffer wasn't set");
        RETURN_NULL();
    }

    /* Retrieve the Message From Friendly Name */
    bsGetFromFriendlyName(Z_STRVAL_P(rawMessageBuffer), &fromFriendlyName);
    RETURN_STRING(fromFriendlyName);
}

PHP_FUNCTION(bounceStudio_MessageHeader)
{
    zval *self = getThis();
    char *messageHeader;
    zval *rawMessageBuffer;

    if ((rawMessageBuffer = zend_hash_str_find(Z_OBJPROP_P(self), "RawMessageBuffer", sizeof("RawMessageBuffer") - 1)) == NULL) {
        zend_error(E_WARNING, "RawMessageBuffer wasn't set");
        RETURN_NULL();
    }

    /* Retrieve the Message Header */
    bsGetHeader(Z_STRVAL_P(rawMessageBuffer), &messageHeader);
    RETURN_STRING(messageHeader);
}

PHP_FUNCTION(bounceStudio_MessageReplyToAddress)
{
    zval *self = getThis();
    char *replyToAdderess;
    zval *rawMessageBuffer;

    if ((rawMessageBuffer = zend_hash_str_find(Z_OBJPROP_P(self), "RawMessageBuffer", sizeof("RawMessageBuffer") - 1)) == NULL) {
        zend_error(E_WARNING, "RawMessageBuffer wasn't set");
        RETURN_NULL();
    }

    /* Retrieve the Message Reply-To Address */
    bsGetReplyToAddress(Z_STRVAL_P(rawMessageBuffer), &replyToAdderess);
    RETURN_STRING(replyToAdderess);
}

PHP_FUNCTION(bounceStudio_MessageReplyToFriendlyName)
{
    zval *self = getThis();
    char *replyToFriendlyName;
    zval *rawMessageBuffer;

    if ((rawMessageBuffer = zend_hash_str_find(Z_OBJPROP_P(self), "RawMessageBuffer", sizeof("RawMessageBuffer") - 1)) == NULL) {
        zend_error(E_WARNING, "RawMessageBuffer wasn't set");
        RETURN_NULL();
    }

    /* Retrieve the Message Reply-To Friendly Name) */
    bsGetReplyToFriendlyName(Z_STRVAL_P(rawMessageBuffer), &replyToFriendlyName);
    RETURN_STRING(replyToFriendlyName);
}

PHP_FUNCTION(bounceStudio_MessageSubject)
{
    zval *self = getThis();
    char *messageSubject;
    zval *rawMessageBuffer;

    if ((rawMessageBuffer = zend_hash_str_find(Z_OBJPROP_P(self), "RawMessageBuffer", sizeof("RawMessageBuffer") - 1)) == NULL) {
        zend_error(E_WARNING, "RawMessageBuffer wasn't set");
        RETURN_NULL();
    }

    /* Retrieve the Message Subject */
    bsGetSubject(Z_STRVAL_P(rawMessageBuffer), &messageSubject);
    RETURN_STRING(messageSubject);
}

PHP_FUNCTION(bounceStudio_MessageToAddress)
{
    zval *self = getThis();
    char *toAddress;
    zval *rawMessageBuffer;

    if ((rawMessageBuffer = zend_hash_str_find(Z_OBJPROP_P(self), "RawMessageBuffer", sizeof("RawMessageBuffer") - 1)) == NULL) {
        zend_error(E_WARNING, "RawMessageBuffer wasn't set");
        RETURN_NULL();
    }

    /* Retrieve the Message To Address */
    bsGetToAddress(Z_STRVAL_P(rawMessageBuffer), &toAddress);
    
    RETURN_STRING(toAddress);
}

PHP_FUNCTION(bounceStudio_MessageToFriendlyName)
{
    zval *self = getThis();
    char *toFriendlyName;
    zval *rawMessageBuffer;

    if ((rawMessageBuffer = zend_hash_str_find(Z_OBJPROP_P(self), "RawMessageBuffer", sizeof("RawMessageBuffer") - 1)) == NULL) {
        zend_error(E_WARNING, "RawMessageBuffer wasn't set");
        RETURN_NULL();
    }

    /* Retrieve the Message To Friendly Name */
    bsGetToFriendlyName(Z_STRVAL_P(rawMessageBuffer), &toFriendlyName);
    RETURN_STRING(toFriendlyName);
}

PHP_FUNCTION(bounceStudio_construct)
{
    bsBounceStudio_init();
    return;
}

static zend_function_entry php_bouncestudio_functions[] = {
    PHP_FE(bounceStudio_DoBounceCheck, NULL)
    PHP_FE(bounceStudio_GetCustomHeaderOriginalMessage, NULL)
    PHP_FE(bounceStudio_GetCustomHeader, NULL)
    PHP_FE(bounceStudio_MessageBody, NULL)
    PHP_FE(bounceStudio_MessageFromAddress, NULL)
    PHP_FE(bounceStudio_MessageFromFriendlyName, NULL)
    PHP_FE(bounceStudio_MessageHeader, NULL)
    PHP_FE(bounceStudio_MessageReplyToAddress, NULL)
    PHP_FE(bounceStudio_MessageReplyToFriendlyName, NULL)
    PHP_FE(bounceStudio_MessageSubject, NULL)
    PHP_FE(bounceStudio_MessageToAddress, NULL)
    PHP_FE(bounceStudio_MessageToFriendlyName, NULL)
    {NULL, NULL, NULL}
};

static zend_function_entry php_bouncestudio_methods[] = {
    {"__construct", PHP_FN(bounceStudio_construct), NULL},
    {"DoBounceCheck", PHP_FN(bounceStudio_DoBounceCheck), NULL},
    {"GetCustomHeaderOriginalMessage", PHP_FN(bounceStudio_GetCustomHeaderOriginalMessage), NULL},
    {"GetCustomHeader", PHP_FN(bounceStudio_GetCustomHeader), NULL},
    {"MessageBody",PHP_FN(bounceStudio_MessageBody), NULL},
    {"MessageFromAddress", PHP_FN(bounceStudio_MessageFromAddress), NULL},
    {"MessageFromFriendlyName",PHP_FN(bounceStudio_MessageFromFriendlyName), NULL},
    {"MessageHeader",PHP_FN(bounceStudio_MessageHeader), NULL},
    {"MessageReplyToAddress",PHP_FN(bounceStudio_MessageReplyToAddress), NULL},
    {"MessageReplyToFriendlyName",PHP_FN(bounceStudio_MessageReplyToFriendlyName), NULL},
    {"MessageSubject",PHP_FN(bounceStudio_MessageSubject), NULL},
    {"MessageToAddress",PHP_FN(bounceStudio_MessageToAddress), NULL},
    {"MessageToFriendlyName",PHP_FN(bounceStudio_MessageToFriendlyName), NULL},
    {NULL, NULL, NULL}
};



PHP_MINIT_FUNCTION(bouncestudio)
{
    zend_class_entry bs;

    INIT_CLASS_ENTRY(bs, "bounceStudio", php_bouncestudio_methods);
    php_bouncestudio_entry = zend_register_internal_class(&bs TSRMLS_CC);

    return SUCCESS;
}



zend_module_entry bouncestudio_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_BOUNCESTUDIO_EXTNAME,
    php_bouncestudio_functions,
    PHP_MINIT(bouncestudio),
    NULL,
    NULL,
    NULL,
    NULL,

#if ZEND_MODULE_API_NO >= 20010901
    PHP_BOUNCESTUDIO_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_BOUNCESTUDIO
ZEND_GET_MODULE(bouncestudio)
#endif
