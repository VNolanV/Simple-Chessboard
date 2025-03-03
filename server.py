import sys
import sqlite3
import sys;
import cgi; 
import hclib;
import json;
import time;
from datetime import datetime

from datetime import datetime

# Web server parts
from http.server import HTTPServer, BaseHTTPRequestHandler
from socketserver import ThreadingMixIn  # For multithreading support
from urllib.parse import urlparse, parse_qsl

#Define global constant for game time
# GAME_TIME = 300 
GAME_TIME = 10

#Initializing the SQLite database and creating necessary tables
def initialize_db():
    conn = sqlite3.connect('hostage_chess.db')  # Create a database file
    c = conn.cursor()

    #Creates table to store chess games
    c.execute('''CREATE TABLE IF NOT EXISTS games (
                    GAME_NO INTEGER PRIMARY KEY AUTOINCREMENT,  --Unique integer identifier for each game
                    WHITE_HANDLE VARCHAR(100) NOT NULL,         --White player's handle (up to 100 characters)
                    BLACK_HANDLE VARCHAR(100) NOT NULL,         --Black player's handle (up to 100 characters)
                    RESULT VARCHAR(256)                         --String of up to 256 characters explaining the outcome of the game
                )''')

    #Creates table to store turns information
    c.execute('''CREATE TABLE IF NOT EXISTS turns (
                    GAME_NO INTEGER NOT NULL,                 --Foreign key referencing games table
                    TURN_NO INTEGER NOT NULL,                 --Sequential number representing the turn in the game
                    TURN CHAR(1) NOT NULL,                    --Indicates whether it is 'w' (White) or 'b' (Black) turn
                    BOARD TEXT NOT NULL,                      --Chessboard representation (fenboard representation)
                    REAL_TIME DATETIME DEFAULT CURRENT_TIMESTAMP, --Timestamp when the move was made
                    WHITE_TIME INTEGER NOT NULL,              --Remaining time for White in seconds
                    BLACK_TIME INTEGER NOT NULL,              --Remaining time for Black in seconds
                    PRIMARY KEY (GAME_NO, TURN_NO),           --Composite primary key on GAME_NO and TURN_NO
                    FOREIGN KEY (GAME_NO) REFERENCES games(GAME_NO) --Enforces reference to games table
                )''')

    c.execute('''CREATE TABLE IF NOT EXISTS movesGameLog (
                    GAME_NO INTEGER NOT NULL,                 --Foreign key referencing games table
                    TURN_NO INTEGER NOT NULL,                 --Sequential number representing the turn in the game
                    TURN CHAR(1) NOT NULL,                    --Indicates whether it is 'w' (White) or 'b' (Black) turn
                    FENBOARD TEXT NOT NULL,                   --Chessboard representation (fenboard representation)
                    PRIMARY KEY (GAME_NO, TURN_NO),           --Composite primary key on GAME_NO and TURN_NO
                    FOREIGN KEY (GAME_NO) REFERENCES games(GAME_NO) --Enforces reference to games table
                )''')

    c.execute('''CREATE TABLE IF NOT EXISTS possibleGames (
                    MOVE_NO INTEGER PRIMARY KEY AUTOINCREMENT,  --Unique integer identifier for each game
                    WHITE_HANDLE VARCHAR(100) NOT NULL,         --White player's handle (up to 100 characters)
                    BLACK_HANDLE VARCHAR(100) NOT NULL,         --Black player's handle (up to 100 characters)
                    RESULT VARCHAR(256)                         --String of up to 256 characters explaining the outcome of the game
                )''')
    #Commit changes and close the connection
    conn.commit()
    conn.close()


# handler for our web-server - handles both GET and POST requests
class MyHandler( BaseHTTPRequestHandler ):
    def do_GET(self):
        # parse the URL to get the path and form data
        parsed  = urlparse( self.path );

        #GET Request For start.html page
        if parsed.path in [ '/start.html' ]:

            fp = open( '.'+self.path );
            content = fp.read();

            self.send_response( 200 );
            self.send_header( "Content-type", "text/html" );
            self.send_header( "Content-length", len( content ) );
            self.end_headers();

            self.wfile.write( bytes( content, "utf-8" ) );
            fp.close();

        #GET Request For The Original upload.html page
        elif parsed.path in [ '/uploadoriginal.html' ]:

            fp = open( '.'+self.path );
            content = fp.read();

            self.send_response( 200 ); 
            self.send_header( "Content-type", "text/html" );
            self.send_header( "Content-length", len( content ) );
            self.end_headers();

            self.wfile.write( bytes( content, "utf-8" ) );
            fp.close();
        
        #GET Request For The upload.html page
        elif parsed.path in [ '/upload.html' ]:

            fp = open( '.'+self.path );
            content = fp.read();

            self.send_response( 200 ); 
            self.send_header( "Content-type", "text/html" );
            self.send_header( "Content-length", len( content ) );
            self.end_headers();

            self.wfile.write( bytes( content, "utf-8" ) );
            fp.close();
        
        #GET Request For The IndexA3.html page
        elif parsed.path in [ '/indexA3.html' ]:

            fp = open( '.'+self.path );
            content = fp.read();

            self.send_response( 200 ); 
            self.send_header( "Content-type", "text/html" );
            self.send_header( "Content-length", len( content ) );
            self.end_headers();

            self.wfile.write( bytes( content, "utf-8" ) );
            fp.close();
        
        #GET Request For The chessboard-1.0.0.css file
        elif parsed.path in [ '/css/chessboard-1.0.0.css' ]:

            fp = open( '.'+self.path );
            content = fp.read();

            self.send_response( 200 ); 
            self.send_header( "Content-type", "text/css" );
            self.send_header( "Content-length", len( content ) );
            self.end_headers();

            self.wfile.write( bytes( content, "utf-8" ) );
            fp.close();
        
        #GET Request For The chessboard-1.0.0.js file
        elif parsed.path in [ '/js/chessboard-1.0.0.js' ]:

            fp = open( '.'+self.path );
            content = fp.read();

            self.send_response( 200 ); 
            self.send_header( "Content-type", "text/js" );
            self.send_header( "Content-length", len( content ) );
            self.end_headers();

            self.wfile.write( bytes( content, "utf-8" ) );
            fp.close();
        
        #GET Request For The All Of The Different Chesspiece IMGs
        elif parsed.path.startswith('/img/chesspieces/wikipedia/'):

            if parsed.path.endswith('bB.png'):
                fp = open( '.'+self.path, 'rb' );
                content = fp.read();

                self.send_response( 200 );
                self.send_header( "Content-type", "image/png" );
                self.send_header( "Content-length", len( content ) );
                self.end_headers();

                self.wfile.write( content );    
                fp.close();
        
            elif parsed.path.endswith('bK.png'):
                fp = open( '.'+self.path, 'rb' );
                content = fp.read();

                self.send_response( 200 ); 
                self.send_header( "Content-type", "image/png" );
                self.send_header( "Content-length", len( content ) );
                self.end_headers();

                self.wfile.write( content );   
                fp.close();
        
            elif parsed.path.endswith('bN.png'):
                fp = open( '.'+self.path, 'rb' );
                content = fp.read();

                self.send_response( 200 ); 
                self.send_header( "Content-type", "image/png" );
                self.send_header( "Content-length", len( content ) );
                self.end_headers();

                self.wfile.write( content );    
                fp.close();
        
            elif parsed.path.endswith('bP.png'):
                fp = open( '.'+self.path, 'rb' );
                content = fp.read();

                self.send_response( 200 );
                self.send_header( "Content-type", "image/png" );
                self.send_header( "Content-length", len( content ) );
                self.end_headers();

                self.wfile.write( content );    
                fp.close();
        
            elif parsed.path.endswith('bQ.png'):
                fp = open( '.'+self.path, 'rb' );
                content = fp.read();

                self.send_response( 200 ); 
                self.send_header( "Content-type", "image/png" );
                self.send_header( "Content-length", len( content ) );
                self.end_headers();

                self.wfile.write( content );   
                fp.close();

            elif parsed.path.endswith('bR.png'):
                fp = open( '.'+self.path, 'rb' );
                content = fp.read();

                self.send_response( 200 ); 
                self.send_header( "Content-type", "image/png" );
                self.send_header( "Content-length", len( content ) );
                self.end_headers();

                self.wfile.write( content );   
                fp.close();

            elif parsed.path.endswith('wB.png'):
                fp = open( '.'+self.path, 'rb' );
                content = fp.read();

                self.send_response( 200 ); 
                self.send_header( "Content-type", "image/png" );
                self.send_header( "Content-length", len( content ) );
                self.end_headers();

                self.wfile.write( content );    
                fp.close();
        
            elif parsed.path.endswith('wK.png'):
                fp = open( '.'+self.path, 'rb' );
                content = fp.read();

                self.send_response( 200 ); 
                self.send_header( "Content-type", "image/png" );
                self.send_header( "Content-length", len( content ) );
                self.end_headers();

                self.wfile.write( content );   
                fp.close();
        
            elif parsed.path.endswith('wN.png'):
                fp = open( '.'+self.path, 'rb' );
                content = fp.read();

                self.send_response( 200 ); 
                self.send_header( "Content-type", "image/png" );
                self.send_header( "Content-length", len( content ) );
                self.end_headers();

                self.wfile.write( content );   
                fp.close();
        
            elif parsed.path.endswith('wP.png'):
                fp = open( '.'+self.path, 'rb' );
                content = fp.read();

                self.send_response( 200 ); 
                self.send_header( "Content-type", "image/png" );
                self.send_header( "Content-length", len( content ) );
                self.end_headers();

                self.wfile.write( content );    
                fp.close();
        
            elif parsed.path.endswith('wQ.png'):
                fp = open( '.'+self.path, 'rb' );
                content = fp.read();

                self.send_response( 200 ); 
                self.send_header( "Content-type", "image/png" );
                self.send_header( "Content-length", len( content ) );
                self.end_headers();

                self.wfile.write( content );    
                fp.close();
        
            elif parsed.path.endswith('wR.png'):
                fp = open( '.'+self.path, 'rb' );
                content = fp.read();

                self.send_response( 200 ); 
                self.send_header( "Content-type", "image/png" );
                self.send_header( "Content-length", len( content ) );
                self.end_headers();

                self.wfile.write( content );   
                fp.close();
        
            else:

                self.send_response( 404 );
                self.end_headers();
                self.wfile.write( bytes( "404: %s not found" % self.path, "utf-8" ) );
        
        #GET Request For The Index.html page
        elif parsed.path in [ '/index.html', '/' ]:

            fp = open( './index.html', 'r' );
            content = fp.read();

            self.send_response( 200 ); 
            self.send_header( "Content-type", "text/html" );
            self.send_header( "Content-length", len( content ) );
            self.end_headers();

            self.wfile.write( bytes( content, "utf-8" ) );
            fp.close();
        
        #GET Request For checkForOpponent function
        elif parsed.path in [ '/check_opponent' ]:

             #Extract the query parameters from the URL
            query_params = dict(parse_qsl(parsed.query))
            game_no = query_params.get("game_no")

            if game_no:

                conn = sqlite3.connect('hostage_chess.db')
                c = conn.cursor()

                #Check if BLACK_HANDLE is set for the given game_no
                c.execute("SELECT BLACK_HANDLE FROM games WHERE GAME_NO = ?", (game_no,))
                result = c.fetchone()
                conn.close()

                if result:
                    black_handle = result[0]

                    # Send the response in JSON format
                    response_data = {
                        'black_handle': black_handle
                    }
                    self.send_response(200)
                    self.send_header("Content-type", "application/json")
                    self.end_headers()
                    self.wfile.write(bytes(json.dumps(response_data), "utf-8"))
                else:
                    # If the game number is not found
                    self.send_response(404)
                    self.end_headers()
                    self.wfile.write(bytes(json.dumps({'error': 'Game not found'}), "utf-8"))
            
            else:
                # If the game_no is not provided
                self.send_response(400)  # Bad Request
                self.end_headers()
                self.wfile.write(bytes(json.dumps({'error': 'Missing game_no parameter'}), "utf-8"))

        #GET Request For checkNewRow function
        elif parsed.path == '/check_new_row':
            #Extracting the query parameters from the URL
            query_params = dict(parse_qsl(parsed.query))
            game_no = query_params.get("game_no")
            nextTurn = query_params.get("nextTurn")

            if game_no and nextTurn:
                conn = sqlite3.connect('hostage_chess.db')
                c = conn.cursor()

                #Query to check for a new row in the 'turns' table based on game_no and nextTurn
                c.execute("SELECT GAME_NO, TURN_NO FROM turns WHERE GAME_NO = ? AND TURN_NO = ?", 
                        (game_no, nextTurn))
                result = c.fetchone()

                if result:
                    #A new row is found
                    response_data = {
                        'new_row_found': True
                       
                    }
                    print("New Row Found")

                else:
                    #No new row found
                    response_data = {
                        'new_row_found': False
                        
                    }
                    print("No New Row Found")

                #Send the response back in JSON format
                self.send_response(200)
                self.send_header("Content-type", "application/json")
                self.end_headers()
                self.wfile.write(bytes(json.dumps(response_data), "utf-8"))

                #Close the connection
                conn.close()

        #GET Request For The history.html page
        elif parsed.path in ['/history.html']:
            #Connect to the SQLite database
            conn = sqlite3.connect('hostage_chess.db')
            c = conn.cursor()

            #Fetch all the games from the games table
            c.execute('SELECT GAME_NO, WHITE_HANDLE, BLACK_HANDLE, RESULT FROM games')
            games = c.fetchall()

            #Build the HTML table dynamically
            table_rows = ''
            for game in games:
                game_no, white_handle, black_handle, result = game
                table_rows += f'<tr onclick="location.href=\'/gamelog.html?GAME_NO={game_no}\'" style="cursor: pointer;">'
                table_rows += f'<td>{game_no}</td><td>{white_handle}</td><td>{black_handle}</td><td>{result}</td>'
                table_rows += '</tr>'

            #Read the base HTML file
            with open('./history.html', 'r') as fp:
                content = fp.read()

            #Inject the table rows into the HTML content (you'll need a placeholder in the HTML for this)
            content = content.replace('{{TABLE_ROWS}}', table_rows)

            #Send the HTTP response with the dynamically generated HTML content
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.send_header("Content-length", len(content))
            self.end_headers()

            self.wfile.write(bytes(content, "utf-8"))

            #Close the database connection
            conn.close()
        
        #GET Request For The gamelog.html page
        elif parsed.path in ['/gamelog.html']:
            
            full_request_path = self.path
            print(f"Full request path: {full_request_path}")

            #Find the GAME_NO by splitting on '=' and getting the last part
            if '=' in full_request_path:
                game_no = full_request_path.split('=')[-1]
            else:
                game_no = None

            #Print the extracted game number for debugging
            print("Extracted game_no: ?", game_no)

            #Connect to the SQLite database
            conn = sqlite3.connect('hostage_chess.db')
            c = conn.cursor()

            self.process_game_moves(game_no)

            result = self.game_result(game_no)

            c.execute('''SELECT TURN_NO, TURN, FENBOARD FROM movesGameLog WHERE GAME_NO = ? ORDER BY TURN_NO''', (game_no,))
            moves = c.fetchall()

            conn.close()

             # Prepare HTML for the game moves and chessboards
            move_html = ''
            chessboard_js = ''
            for index, move in enumerate(moves):
                turn_no, turn, fenboard = move

                # Create a unique div id for each chessboard
                div_id = f"board_{index}"
                
                # Add a row in the table for the move
                move_html += f'<tr><td>{turn_no}</td><td>{turn}</td><td>{fenboard}</td></tr>'
                
                # Generate a div and JS for each chessboard
                move_html += f'<div id="{div_id}" style="width: 400px; margin-bottom: 20px;"></div>'
                chessboard_js += f'''
                    var board{index} = Chessboard('{div_id}', {{
                        draggable: true,
                        dropOffBoard: 'snapback',
                        position: '{fenboard}',
                        pieceTheme: '/img/chesspieces/wikipedia/{{piece}}.png',
                    }});
                '''

            # Read the base HTML file
            with open('./gamelog.html', 'r') as fp:
                content = fp.read()

            # Inject the dynamic content into the HTML
            content = content.replace('{{TABLE_ROWS}}', move_html)  # Inject game moves and chessboards
            content = content.replace('{{GAME_RESULT}}', result)    # Inject game result
            content = content.replace('{{CHESSBOARD_JS}}', chessboard_js)  # Inject JavaScript for all chessboards

            # Send the response
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.end_headers()
            self.wfile.write(bytes(content, "utf-8"))
            
        #404 End Response
        else:

            self.send_response( 404 );
            self.end_headers();
            self.wfile.write( bytes( "404: %s not found" % self.path, "utf-8" ) );


    def do_POST(self):
        parsed = urlparse(self.path)


        #POST request for display.html
        if parsed.path == '/display.html':
            form = cgi.FieldStorage(fp=self.rfile,
                                    headers=self.headers,
                                    environ={'REQUEST_METHOD': 'POST',
                                              'CONTENT_TYPE': self.headers['Content-Type']})

            #Extracting the stringboard from the form data
            #stringboard_data = form.getvalue('stringboard')

            stringboard_data = form["stringboard"].file.read().decode('utf-8')         

            #Call the C functions to convert the stringboard and enerate the FEN string
            board = hclib.boardstring(stringboard_data) 
            active = "w"  #Tempexample
            castling = "-"  #Tempexample
            enpassant = "-"  #Tempexample
            half = 0  #Tempexample
            full = 1  #Tempexample
            fen_string = hclib.fen(board, active, castling, enpassant, half, full) 

            #Read the HTML template from display.html
            with open('display.html', 'r') as html_file:
                html_template = html_file.read()

            #Create the final HTML output by injecting the FEN string into the template
            html_output = html_template.replace("{{fen_string}}", fen_string)

            #Send the response back to the browser
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.send_header("Content-length", len(html_output))
            self.end_headers()
            self.wfile.write(bytes(html_output, "utf-8"))

        #POST request for board.html
        elif parsed.path == '/board.html':
            form = cgi.FieldStorage(fp=self.rfile,
                                    headers=self.headers,
                                    environ={'REQUEST_METHOD': 'POST',
                                              'CONTENT_TYPE': self.headers['Content-Type']})

            #Extracting the stringboard from the form data
            stringboard_data = form["stringboard"].file.read().decode('utf-8')

            #Assigning local variables for turn, wtime and btime
            turn = form.getvalue("turn")  #Turn (w or b)
            try:
                wtime = int(form.getvalue("wtime"))
            except (TypeError, ValueError):
                wtime = 0  #Fallback to 0 if the value is missing or invalid

            try:
                btime = int(form.getvalue("btime"))
            except (TypeError, ValueError):
                btime = 0 #Fallback to 0 if the value is missing or invalid

                       

            #Call the C functions to convert the stringboard and enerate the FEN string
            board = hclib.boardstring(stringboard_data) 
            active = "w"  #Tempexample
            castling = "-"  #Tempexample
            enpassant = "-"  #Tempexample
            half = 0  #Tempexample
            full = 1  #Tempexample
            fen_string = hclib.fen(board, active, castling, enpassant, half, full) 

            #Read the HTML template from display.html
            with open('indexA3.html', 'r') as html_file:
                html_template = html_file.read()

            #Create the final HTML output by injecting the FEN string and other values into the template
            html_output = (html_template
               .replace("{{fen_string}}", fen_string)
               .replace("{{turn}}", turn)
               .replace("{{wtime}}", str(wtime))  # Convert wtime to string
               .replace("{{btime}}", str(btime))  # Convert btime to string
              )
            #Send the response back to the browser
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.send_header("Content-length", len(html_output))
            self.end_headers()
            self.wfile.write(bytes(html_output, "utf-8"))

        #POST request for login.html
        elif parsed.path == '/login.html':
            form = cgi.FieldStorage(fp=self.rfile,
                                    headers=self.headers,
                                    environ={'REQUEST_METHOD': 'POST',
                                              'CONTENT_TYPE': self.headers['Content-Type']})


            #Assigning local variables login handle
            loginhandle = form.getvalue("loginhandle") 

            print(loginhandle)            

            conn = sqlite3.connect('hostage_chess.db')
            c = conn.cursor()

            c.execute("SELECT GAME_NO FROM games WHERE BLACK_HANDLE = '' LIMIT 1")
            game = c.fetchone()

            if game is None:
                print("Case 1: No waiting games, creating a new game. User assigned to WHITE_HANDLE")
                c.execute("SELECT MAX(GAME_NO) FROM games")
                max_game_no = c.fetchone()[0]
                if max_game_no is None:
                    max_game_no = 0  # Start with 0 if no games exist
                new_game_no = max_game_no + 1

                print(new_game_no)
                print(loginhandle)

                # Create a new game with WHITE_HANDLE as the current player
                c.execute('''INSERT INTO games (GAME_NO, WHITE_HANDLE, BLACK_HANDLE, RESULT)
                             VALUES (?, ?, '', '')''', (new_game_no, loginhandle))
                conn.commit()

                # Send "Waiting for opponent" message
                with open('waiting.html', 'r') as html_file:
                    html_template = html_file.read()


                # Send the GAME_NO as part of the Javascript for polling
                html_output = (html_template
                    .replace("{{new_game_no}}", str(new_game_no))
                  )

                self.send_response(200)
                self.send_header("Content-type", "text/html")
                self.send_header("Content-length", len(html_output))
                self.end_headers()
                self.wfile.write(bytes(html_output, "utf-8"))

            else:
                print("Case 2: Joining an existing game by filling in the BLACK_HANDLE")
                game_no = game[0]
                c.execute('''UPDATE games SET BLACK_HANDLE = ? WHERE GAME_NO = ?''', (loginhandle, game_no))

                # Initialize the turns table for this game with the starting position
                new_board = hclib.newboard() 
                active = "w"  #Tempexample
                castling = "-"  #Tempexample
                enpassant = "-"  #Tempexample
                half = 0  #Tempexample
                full = 1  #Tempexample
                fenString = hclib.fen(new_board, active, castling, enpassant, half, full) 

                real_time = datetime.now()


                c.execute('''INSERT INTO turns (GAME_NO, TURN_NO, TURN, BOARD, REAL_TIME, WHITE_TIME, BLACK_TIME)
                             VALUES (?, ?, ?, ?, ?, ?, ?)''', (game_no, 1, 'w', fenString, real_time, GAME_TIME, GAME_TIME))

                conn.commit()

                # Create a form to POST the game_no and turn_no to /opponent.html
                html_output = f"""
                <html>
                <body>
                    <form id="opponentForm" action="/opponent.html" method="POST">
                        <input type="hidden" name="game_no" value="{game_no}">
                        <input type="hidden" name="turn_no" value="0">
                    </form>
                    <script>
                        document.getElementById('opponentForm').submit();  // Automatically submit the form
                    </script>
                </body>
                </html>
                """

                self.send_response(200)
                self.send_header("Content-type", "text/html")
                self.send_header("Content-length", len(html_output))
                self.end_headers()
                self.wfile.write(bytes(html_output, "utf-8"))

            conn.close()

        #POST request for player.html
        elif parsed.path == '/player.html':
            form = cgi.FieldStorage(fp=self.rfile,
                                    headers=self.headers,
                                    environ={'REQUEST_METHOD': 'POST',
                                              'CONTENT_TYPE': self.headers['Content-Type']})

            print("Displaying player.html")

            #Retrieving GAME_NO and TURN_NO from the form data
            game_no = form.getvalue("game_no")
            turn_no = form.getvalue("turn_no")           

            #Connecting to the database
            conn = sqlite3.connect('hostage_chess.db')
            c = conn.cursor()

            #Searching for the game data based on GAME_NO and TURN_NO
            c.execute('''SELECT TURN, BOARD, REAL_TIME, WHITE_TIME, BLACK_TIME 
                        FROM turns WHERE GAME_NO = ? AND TURN_NO = ?''', (game_no, turn_no))
            game_data = c.fetchone()
            conn.close()

            if game_data is not None:

                print("Game Data Exists")
                turn, fenString, real_time, white_time, black_time = game_data

                print(fenString)

                #Read the player.html template
                with open('player.html', 'r') as html_file:
                    html_template = html_file.read()

                # Create the final HTML output by injecting the FEN string and other values into the template
                html_output = (html_template
                    .replace("{{fen_string}}", fenString)
                    .replace("{{turn}}", turn)
                    .replace("{{wtime}}", str(white_time))  
                    .replace("{{btime}}", str(white_time))  
                    .replace("{{game_no}}", game_no)  
                    .replace("{{turn_no}}", turn_no) 
                )

                # Send the response back to the browser
                self.send_response(200)
                self.send_header("Content-type", "text/html")
                self.send_header("Content-length", len(html_output))
                self.end_headers()
                self.wfile.write(bytes(html_output, "utf-8"))

        #POST request for opponent.html
        elif parsed.path == '/opponent.html':
            #Parse form data
            form = cgi.FieldStorage(fp=self.rfile,
                                    headers=self.headers,
                                    environ={'REQUEST_METHOD': 'POST',
                                             'CONTENT_TYPE': self.headers['Content-Type']})

            print("Displaying opponent.html")
            
            #Retrieve GAME_NO, TURN_NO, and optionally board state
            game_no = form.getvalue("game_no")
            turn_no = form.getvalue("turn_no")
            fenStringInput = form.getvalue("fenString")  # May be None if not provided

            #Redirect boolean
            redirect = "f"

            #Holder Value For New Turn_No
            updatedTurnNoHolder = 0;

            print(fenStringInput)
            
            #Connect to the database
            conn = sqlite3.connect('hostage_chess.db')
            c = conn.cursor()

            c.execute('''SELECT RESULT FROM games WHERE GAME_NO = ?''',(game_no))
            resultTest = c.fetchone()

            print(resultTest[0])

            if resultTest[0] == "":

                if fenStringInput == '' or fenStringInput == None:

                    time.sleep(2)

                    c.execute('''SELECT TURN_NO, BOARD 
                                FROM turns WHERE GAME_NO = ? AND TURN_NO = (SELECT MAX(TURN_NO) FROM turns WHERE GAME_NO = ?)''', 
                                (game_no, game_no))

                    # Retrieve the result
                    row = c.fetchone()

                    turns_no, fenString = row

                    self.send_opponent_page(game_no, turns_no, fenString)

                else:

                    c.execute('''SELECT TURN, BOARD, REAL_TIME, WHITE_TIME, BLACK_TIME 
                                FROM turns WHERE GAME_NO = ? AND TURN_NO = ? ''', (game_no,turn_no))
                    last_turn = c.fetchone()

                    lastTurn, lastBoard, lastRealTimes, lastWhiteTime, lastBlackTime = last_turn

                    lastRealTime = datetime.strptime(lastRealTimes, '%Y-%m-%d %H:%M:%S.%f')

                    #Updating turn number

                    print(turn_no)

                    updatedTurnNo = int(turn_no) + 1

                    updatedTurnNoHolder = updatedTurnNo

                    print(updatedTurnNo)

                    #Updating times

                    nowTime = datetime.now()

                    timeDifferenc = nowTime - lastRealTime

                    timeDifference = timeDifferenc.total_seconds()

                    if lastTurn == 'w':
                        nextTurn = 'b'
                        newWhiteTime = lastWhiteTime - timeDifference
                        newBlackTime = lastBlackTime

                        if newWhiteTime < 0:
                            newWhiteTime = 0
                            result = "Game Over --- Black Wins: White Ran Out Of Time"
                            c.execute('''UPDATE games SET RESULT = ? WHERE GAME_NO = ?''', (result, game_no))
                            conn.commit()
                            redirect = "t"


                    else:
                        nextTurn = 'w'
                        newBlackTime = lastBlackTime - timeDifference
                        newWhiteTime = lastWhiteTime

                        if newBlackTime < 0:
                            newBlackTime = 0
                            result = "Game Over --- White Wins: Black Ran Out Of Time"
                            c.execute('''UPDATE games SET RESULT = ? WHERE GAME_NO = ?''', (result, game_no))
                            conn.commit()
                            redirect = "t"

                    if "k" not in fenStringInput:
                        result = "Game Over --- White Wins: Black King Was Taken"
                        c.execute('''UPDATE games SET RESULT = ? WHERE GAME_NO = ?''', (result, game_no))
                        conn.commit()
                        redirect = "t"
                        
                    elif "K" not in fenStringInput:
                        result = "Game Over --- Black Wins: White King Was Taken"
                        c.execute('''UPDATE games SET RESULT = ? WHERE GAME_NO = ?''', (result, game_no))
                        conn.commit()
                        redirect = "t"


                    c.execute('''INSERT INTO turns (GAME_NO, TURN_NO, TURN, BOARD, REAL_TIME, WHITE_TIME, BLACK_TIME)
                                VALUES (?, ?, ?, ?, ?, ?, ?)''', (game_no, updatedTurnNo, nextTurn, fenStringInput, nowTime, newWhiteTime, newBlackTime))
                    conn.commit()
            
                    if redirect == "t":
                        conn.close()
                        self.send_game_end_response(game_no, result)
                    else:
                        # Continue processing
                        self.send_opponent_page(game_no, updatedTurnNo, fenStringInput)
            
            else:

                resultTestStr = str(resultTest[0])
                self.send_game_end_response(game_no, resultTestStr)

            conn.close()

        #404 End Response
        else:
            self.send_response(404)
            self.end_headers()
            self.wfile.write(bytes("404: %s not found" % self.path, "utf-8"))

    #Function for sending game end response and page
    def send_game_end_response(self, game_no, result):
        """Helper function to send the ending HTML page with game results."""
        with open('ending.html', 'r') as html_file:
            html_template = html_file.read()

        print(result)

        html_output = html_template.replace('{{result}}', result)
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.send_header("Content-length", len(html_output))
        self.end_headers()
        self.wfile.write(bytes(html_output, "utf-8"))

    #Function for serving opponent page to help de-clutter post request
    def send_opponent_page(self, game_no, turn_no, fenStringInput):
        """Helper function to send the updated opponent page."""
        with open('opponent.html', 'r') as html_file:
            html_template = html_file.read()

        html_output = (html_template
            .replace("{{game_no}}", str(game_no))
            .replace("{{turn_no}}", str(turn_no))
            .replace("{{fenString}}", fenStringInput)
        )
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.send_header("Content-length", len(html_output))
        self.end_headers()
        self.wfile.write(bytes(html_output, "utf-8"))

    #Function for processing all the moves of specific game and moving them to a table for easy access
    def process_game_moves(self, game_no):
        #Connect to the SQLite database
        conn = sqlite3.connect('hostage_chess.db')
        c = conn.cursor()

        #Step 1: Clear all data in the movesGameLog table 
        c.execute('''DELETE FROM movesGameLog''')
        
        #Step 2: Fetch all the turns for the given game number
        c.execute('''SELECT TURN_NO, TURN, BOARD
                    FROM turns WHERE GAME_NO = ? ORDER BY TURN_NO''', (game_no,))
        
        turns = c.fetchall()  #Fetching all rows for the game

        #Step 3: Check how many results were returned
        num_turns = len(turns)
        print(f"Found {num_turns} turns for game {game_no}.")

        if num_turns == 0:
            print("No turns found for this game.")
            return

        #Step 4: Create the movesGameLog table (if it doesn't already exist)
        c.execute('''CREATE TABLE IF NOT EXISTS movesGameLog (
						GAME_NO INTEGER NOT NULL,                 --Foreign key referencing games table
						TURN_NO INTEGER NOT NULL,                 --Sequential number representing the turn in the game
						TURN CHAR(1) NOT NULL,                    --Indicates whether it is 'w' (White) or 'b' (Black) turn
						FENBOARD TEXT NOT NULL,                   --Chessboard representation (fenboard representation)
						PRIMARY KEY (GAME_NO, TURN_NO),           --Composite primary key on GAME_NO and TURN_NO
						FOREIGN KEY (GAME_NO) REFERENCES games(GAME_NO) --Enforces reference to games table
					)''')

        #Step 5: Loop through the results and insert data into the movesGameLog table
        for turn in turns:
            turn_no, turn, board = turn
            
            #Step 6: Rename board to fenboard for clarity
            fenboard = board  

            # Step 7: Insert the new data into the movesGameLog table
            c.execute('''INSERT OR REPLACE INTO movesGameLog 
                        (GAME_NO, TURN_NO, TURN, FENBOARD) 
                        VALUES (?, ?, ?, ?)''', 
                    (game_no, turn_no, turn, fenboard))

        #Commit changes and close the connection
        conn.commit()
        conn.close()

    #Function for returning the result of a specific game
    def game_result(self, game_no):
        
        conn = sqlite3.connect('hostage_chess.db')
        c = conn.cursor()
       
        c.execute('''SELECT RESULT FROM games WHERE GAME_NO = ?''', (game_no,))
        result = c.fetchone()  
        conn.close()

        if result:
            return result[0]  
        else:
            return "Game not found."  

class ThreadedHTTPServer(ThreadingMixIn, HTTPServer):
    """Handle requests in a separate thread."""

if __name__ == "__main__":

    #Initializing the database when the server starts
    initialize_db()

    #Start the server on the specified port
    httpd = ThreadedHTTPServer(('0.0.0.0', int(sys.argv[1])), MyHandler)
    print("Server listing in port:  ", int(sys.argv[1]))
    httpd.serve_forever()

