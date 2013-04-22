#!/usr/bin/env python
import MySQLdb as mysql
import conf


db = mysql.connect(host=conf.SQL_HOST,
	user=conf.SQL_USER,
	passwd=conf.SQL_PASSWORD,
	db=conf.SQL_DATABASE)

def add_to_nodboard(status_id, user_id):
	cursor = db.cursor()
	cursor.execute(
            """
            INSERT INTO nodboard (
              status_id, user_id, nodboard_date
            ) VALUES (
              '%s', '%s', UTC_TIMESTAMP()
            )
            """ % (status_id, user_id))
	cursor.close()
	

def main():
	cursor = db.cursor(mysql.cursors.DictCursor)
	cursor.execute(
            """
            SELECT 
              next_nodboard.status_id,
              next_nodboard.user_id
            FROM next_nodboard
            ORDER BY next_nodboard.status_id ASC
            """)
	result = cursor.fetchall()
	cursor.close()
	[add_to_nodboard(row['status_id'], row['user_id']) for row in result]
	db.commit()
	db.close()

if __name__ == '__main__':
	main()

