DELETE FROM status WHERE status.id NOT IN (SELECT status_id FROM favorite);

DELETE FROM favorite WHERE favorite.status_id IN (SELECT status.id FROM status WHERE on_leaderboard = false);
