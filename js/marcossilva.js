 $(window).load( function() {  

                         $('#mycalendar').monthly({
                         mode: 'event',

                         });

                         $('#mycalendar2').monthly({   
                         mode: 'picker',   
                         target: '#mytarget',   
                         setWidth: '250px',   
                         startHidden: true,   
                         showTrigger: '#mytarget',
                         stylePast: true,
                         disablePast: true 
                         });  

                         switch(window.location.protocol) {  
                         case 'http:': 
                         case 'https:':  
                         // running on a server, should be good. 
                         break;  
                         case 'file:':   
                         //alert('Bem vindos ao RID, algumas funcionalidades não estaram disponivel até que realize o login...');
                         }  

                         });   
                         </script>
                         <!-- //calendar -->
