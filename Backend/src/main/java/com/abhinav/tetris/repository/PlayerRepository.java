package com.abhinav.tetris.repository;

import com.abhinav.tetris.model.Player;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface PlayerRepository extends JpaRepository<Player, Long> {
    Optional<Player> findByPlayerName(String playerName);
    boolean existsByPlayerName(String playerName);
}
