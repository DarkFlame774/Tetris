package com.abhinav.tetris.repository;

import com.abhinav.tetris.dto.LeaderboardEntityRepresentation;
import com.abhinav.tetris.model.GameSession;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface GameSessionRepository extends JpaRepository<GameSession, Long> {
    @Query("""
        SELECT new com.abhinav.tetris.dto.LeaderboardEntityRepresentation(
            gs.player.id,
            gs.player.playerName,
            Max(gs.score)
        )
        from GameSession gs
        Group by gs.player.id,gs.player.playerName
        Order by Max(gs.score) desc
        """)
    List<LeaderboardEntityRepresentation> findAllByBestScore();
}
