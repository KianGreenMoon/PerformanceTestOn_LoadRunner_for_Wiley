formsParser()
{
	char * bufferToSearch = lr_eval_string("{parse}");
    int matchCt, ord;
    char *arrayMemberValue;
    
    //parse all strings with 'p' tag
    lr_save_param_regexp (
        bufferToSearch,
               strlen(bufferToSearch),
               "RegExp=<p>(.+)</p>",
               "Ordinal=All",
               "ResultParam=PStrings",
               LAST );

    matchCt = lr_paramarr_len("PStrings");

    lr_message("%d match(es) found.", matchCt);

    for (ord=1; ord <= matchCt; ord++){
    	
    	arrayMemberValue = lr_paramarr_idx("PStrings", ord);
    	
	lr_save_int(ord, "ordinal");
	
    //Name (ID) of text form
    lr_save_param_regexp (
        arrayMemberValue,
               strlen(arrayMemberValue),
               "RegExp=<input type=\"text\" name=\"(\\w+)\">",
               "Ordinal=1",
               lr_eval_string("ResultParam=inputName_{ordinal}"),
               LAST );
    if( strcmp (lr_eval_string(lr_eval_string("{inputName_{ordinal}}")),  lr_eval_string("{inputName_{ordinal}}")) != 0 ) {
    	lr_log_message("LOG: This is a text");
		lr_save_string("test", lr_eval_string("inputValue_{ordinal}"));
    }
    
    else {
    
    //Name (ID) of select form
    lr_save_param_regexp (
        arrayMemberValue,
               strlen(arrayMemberValue),
               "RegExp=<select name=\"(\\w+)\">",
               "Ordinal=1",
               lr_eval_string("ResultParam=inputName_{ordinal}"),
               LAST );
    
   if( strcmp (lr_eval_string(lr_eval_string("{inputName_{ordinal}}")),  lr_eval_string("{inputName_{ordinal}}")) != 0 ) {
    	lr_log_message("LOG: This is a select");
    	findLongestValue(arrayMemberValue);
    }
    
    else {
    
    
    //Name (ID) of radio form
    lr_save_param_regexp (
        arrayMemberValue,
               strlen(arrayMemberValue),
               "RegExp=<input type=\"radio\" name=\"(\\w+)\"",
               "Ordinal=1",
               lr_eval_string("ResultParam=inputName_{ordinal}"),
               LAST );
    	
    if( strcmp (lr_eval_string(lr_eval_string("{inputName_{ordinal}}")),  lr_eval_string("{inputName_{ordinal}}")) != 0 ) {
    	lr_log_message("LOG: This is a radio");
    }
    
    else {
    	lr_log_message("LOG: another type");    
    }}}
    
    }
    
	return 0;
}

findLongestValue(char *arrayMemberValue) {
	//Find the longest value
	lr_save_param_regexp (
	    arrayMemberValue,
	           strlen(arrayMemberValue),
	           "RegExp=<option value=\"(\\w+)\">",
	           "Ordinal=ALL",
	           lr_eval_string("ResultParam=selectValues"),
	           LAST );
}