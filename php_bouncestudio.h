#ifndef PHP_BOUNCESTUDIO_H
#define PHP_BOUNCESTUDIO_H 1

#define PHP_BOUNCESTUDIO_VERSION "3.7"
#define PHP_BOUNCESTUDIO_EXTNAME "BounceStudio API"


PHP_FUNCTION(bounceStudio_DoBounceCheck);
PHP_FUNCTION(bounceStudio_GetCustomHeaderOriginalMessage);
PHP_FUNCTION(bounceStudio_GetCustomHeader);
PHP_FUNCTION(bounceStudio_MessageBody);
PHP_FUNCTION(bounceStudio_MessageFromAddress); 
PHP_FUNCTION(bounceStudio_MessageFromFriendlyName); 
PHP_FUNCTION(bounceStudio_MessageHeader); 
PHP_FUNCTION(bounceStudio_MessageReplyToAddress); 
PHP_FUNCTION(bounceStudio_MessageReplyToFriendlyName); 
PHP_FUNCTION(bounceStudio_MessageSubject); 
PHP_FUNCTION(bounceStudio_MessageToAddress); 
PHP_FUNCTION(bounceStudio_MessageToFriendlyName); 



extern zend_module_entry bouncestudio_module_entry;
#define phpext_bouncestudio_ptr &bouncestudio_module_entry

#endif
