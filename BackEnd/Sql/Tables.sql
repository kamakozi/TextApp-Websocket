CREATE TABLE IF NOT EXISTS role (
      id SERIAL PRIMARY KEY,
      roles TEXT UNIQUE NOT NULL
);

INSERT INTO role (roles)
VALUES ('admin'), ('user')
    ON CONFLICT DO NOTHING;

CREATE TABLE IF NOT EXISTS users (
       id SERIAL PRIMARY KEY,
       username TEXT UNIQUE NOT NULL,
       hashed_password TEXT NOT NULL,
       email TEXT NOT NULL,
       role_id INTEGER,
       created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
       token TEXT,
       photo BYTEA,
       FOREIGN KEY (role_id) REFERENCES role(id) ON DELETE SET NULL
    );

CREATE TABLE IF NOT EXISTS session (
       id SERIAL PRIMARY KEY,
       sender_id INTEGER NOT NULL,
       reciver_id INTEGER NOT NULL,
       refresh_token TEXT NOT NULL,
       create_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
       expires_at TIMESTAMP,
       FOREIGN KEY (sender_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (reciver_id) REFERENCES users(id) ON DELETE CASCADE
    );

CREATE TABLE IF NOT EXISTS message (
       id SERIAL PRIMARY KEY,
       sender_id INTEGER NOT NULL,
       reciver_id INTEGER NOT NULL,
       content TEXT NOT NULL,
       sent_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
       FOREIGN KEY (sender_id) REFERENCES users(id) ON DELETE CASCADE,
      FOREIGN KEY (reciver_id) REFERENCES users(id) ON DELETE CASCADE
    );