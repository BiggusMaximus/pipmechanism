CREATE TABLE pipmechanism (
    id INT AUTO_INCREMENT PRIMARY KEY,
    tegangan FLOAT,
    arus FLOAT,
    timestamp_column TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);
