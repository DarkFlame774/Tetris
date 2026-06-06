package com.abhinav.tetris.service;

import com.abhinav.tetris.dto.LoginRequest;
import com.abhinav.tetris.dto.LoginResponse;
import com.abhinav.tetris.dto.RegisterRequest;
import com.abhinav.tetris.model.Player;
import com.abhinav.tetris.repository.PlayerRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.Objects;
import java.util.Optional;

@Service
public class PlayerService {
    private final PlayerRepository playerRepo;

    @Autowired
    public PlayerService(PlayerRepository playerRepo) {
        this.playerRepo = playerRepo;
    }

    public void registerPlayer(RegisterRequest request){

        if (playerRepo.existsByPlayerName(request.name())){
            throw new IllegalArgumentException("Player name already Taken Chose another.");
        }

        Player player = Player.builder()
                .playerName(request.name())
                .hashPasswd(request.password())
                .registeredAt(LocalDateTime.now())
                .updatedAt(LocalDateTime.now())
                .build();

        playerRepo.save(player);
    }

    public LoginResponse loginPlayer(LoginRequest request){

        Player player = playerRepo.findByPlayerName(request.name())
                .orElseThrow(() ->
                        new IllegalStateException("Player does not exist"));

        if(!Objects.equals(request.password(), player.getHashPasswd())){
            throw new IllegalStateException("Wrong Password. Try again");
        }

        return new LoginResponse(
                player.getId(),
                player.getPlayerName(),
                player.getRegisteredAt().toLocalDate());
    }
}
