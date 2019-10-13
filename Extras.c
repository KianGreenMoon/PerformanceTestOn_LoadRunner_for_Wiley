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
	    
	    //Name (ID) of select form
	    lr_save_param_regexp (
	        arrayMemberValue,
	               strlen(arrayMemberValue),
	               "RegExp=<select name=\"(\\w+)\">",
	               "Ordinal=1",
	               lr_eval_string("ResultParam=inputName_{ordinal}"),
	               LAST );
	    
	    //Name (ID) of radio form
	    lr_save_param_regexp (
	        arrayMemberValue,
	               strlen(arrayMemberValue),
	               "RegExp=<input type=\"radio\" name=\"(\\w+)\"",
	               "Ordinal=1",
	               lr_eval_string("ResultParam=inputName_{ordinal}"),
	               LAST );

	    
	    //Value of the text form
		//lr_save_string("test", lr_eval_string("inputValue_{ordinal}"));
    }
    
	return 0;
}
