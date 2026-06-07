package com.abhinav.tetris.service;

import com.abhinav.tetris.dto.EndGameSessionRequest;
import com.abhinav.tetris.dto.StartGameSessionRequest;
import com.abhinav.tetris.dto.StartGameSessionResponse;
import com.abhinav.tetris.model.GameSession;
import com.abhinav.tetris.model.Player;
import com.abhinav.tetris.repository.GameSessionRepository;
import com.abhinav.tetris.repository.PlayerRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.Duration;
import java.time.LocalDateTime;
import java.time.LocalTime;

@Service
public class GameSessionService {
    private final GameSessionRepository gameSessionRepository;
    private final PlayerRepository playerRepo;

    @Autowired
    public GameSessionService(GameSessionRepository gameSessionRepository, PlayerRepository playerRepo) {
        this.gameSessionRepository = gameSessionRepository;
        this.playerRepo = playerRepo;
    }

    public StartGameSessionResponse startGameSession(StartGameSessionRequest request){
        Player player = playerRepo.findByPlayerName(request.name())
                .orElseThrow(() ->
                        new IllegalStateException("Invalid Session"));

        GameSession gameSession = GameSession.builder()
                .player(player)
                .sessionStart(LocalDateTime.now())
                .build();

        gameSessionRepository.save(gameSession);
        return new StartGameSessionResponse(
                gameSession.getId());
    }

    public void endGameSession(Long sessionId, EndGameSessionRequest request){
        GameSession gameSession = gameSessionRepository.findById(sessionId)
                .orElseThrow(() ->
                        new IllegalStateException("Unexpected Error During Saving Session Details"));

        LocalDateTime sessionEnd = LocalDateTime.now();
        Long duration = Duration.between(gameSession.getSessionStart(),sessionEnd).getSeconds();
        gameSession.setSessionEnd(sessionEnd);
        gameSession.setDurationSeconds(duration);
        gameSession.setScore(request.score());
        gameSession.setLineCleared(request.linesCleared());
        gameSessionRepository.save(gameSession);
    }
}
