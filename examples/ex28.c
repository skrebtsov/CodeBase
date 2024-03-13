/* The result put into 'to' will be "C B A" */
c4encode( to, "ABC", "3 2 1", "123" ) ;

/* The result put into 'to' will be "A&B&C" */
c4encode( to, "30-12/1990", "789A4512", "123456789A" ) ;

/* The result put into 'to' will be "12/30/90" */
c4encode( to, "19901230", "EF/GH/CD", "ABCDEFGH" ) ;
