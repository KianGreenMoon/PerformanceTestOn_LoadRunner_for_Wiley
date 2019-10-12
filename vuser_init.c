/*
	Author: Kian Eugen Seibel (Евгений Алексеевич Сайбель)
	Project: http://test.youplace.net
	Date: 12.10.2019
	
	Description:
		1. Enter the portal
		-- loop
		2. INPUT[@type=text] field must be filled in with "test" value
		3. INPUT[@type=radio] field must be selected with the longest value 
		4. SELECT field must be selected with the longest value
		5. Push 'Submit' button
		-- ERROR: one or several values are incorrect ? end loop with Fail status : continue
		-- Success ? end loop with Pass status : continue
		
		ERROR: one or several values are incorrect => Fail     X
		Success 								   => Pass 	   X
		Next question							   => Continue X
		
		
*/

vuser_init()
{
	return 0;
}
