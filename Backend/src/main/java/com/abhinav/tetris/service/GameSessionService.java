package com.abhinav.tetris.service;

import com.abhinav.tetris.dto.*;
import com.abhinav.tetris.model.GameSession;
import com.abhinav.tetris.model.Player;
import com.abhinav.tetris.repository.GameSessionRepository;
import com.abhinav.tetris.repository.PlayerRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.Duration;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.List;

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
        Player player = playerRepo.findById(request.id())
                .orElseThrow(() ->
                        new IllegalStateException("Invalid Session"));

        GameSession gameSession = GameSession.builder()
                .player(player)
                .score(0L)
                .lineCleared(0L)
                .sessionStart(LocalDateTime.now())
                .build();

        gameSessionRepository.save(gameSession);
        return new StartGameSessionResponse(
                gameSession.getId());
    }

    public void endGameSession(EndGameSessionRequest request){
        GameSession gameSession = gameSessionRepository.findById(request.sessionId())
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

    public LeaderboardResponse getLeaderBoard(LeaderboardRequest request){
        List<LeaderboardEntityRepresentation> players = gameSessionRepository.findAllByBestScore();
        List<LeaderboardRankRepresentation> topPlayers = new ArrayList<>();
        LeaderboardRankRepresentation currentPlayer = null;
        for(int i = 0; i < players.size(); i++){
            if( i < 3) {
                topPlayers.add(new LeaderboardRankRepresentation(
                                i + 1L,
                                players.get(i).name(),
                                players.get(i).bestScore()
                        )
                );
            }
            if (players.get(i).id().equals(request.id())){
                currentPlayer = new LeaderboardRankRepresentation(
                        i + 1L,
                        players.get(i).name(),
                        players.get(i).bestScore()
                );
            }
        }

        return new LeaderboardResponse(
                topPlayers,
                currentPlayer
        );
    }
}
